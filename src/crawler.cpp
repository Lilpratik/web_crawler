#include "crawler.h"
#include "html_parser.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <filesystem> // For creating directories

// Callback function for cURL to write data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    userData->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Constructor
Crawler::Crawler() : outputFilePath("data/output.json") {
    // Ensure the "data" directory exists
    std::filesystem::create_directories("data");
}

// Add a seed URL
void Crawler::addSeedUrl(const std::string& url) {
    urlQueue.push(url);
}

// Crawl a single URL
void Crawler::crawlUrl(const std::string& url) {
    CURL* curl = curl_easy_init(); // Initialize cURL
    if (!curl) {
        std::cerr << "Failed to initialize cURL.\n";
        return;
    }

    std::string response; // String to hold the HTML content
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());           // Set URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set write callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);       // Set user data for the callback
    CURLcode res = curl_easy_perform(curl); // Perform the cURL operation
    curl_easy_cleanup(curl);                // Cleanup cURL resources

    if (res != CURLE_OK) {
        std::cerr << "Error fetching URL: " << url << " - " << curl_easy_strerror(res) << "\n";
        return;
    }

    // Parse HTML and extract links
    std::vector<std::string> links = HtmlParser::extractLinks(response);

    // Add new links to the queue
    {
        std::lock_guard<std::mutex> lock(queueMutex); // Thread-safe access
        for (const auto& link : links) {
            if (visited.find(link) == visited.end()) {
                urlQueue.push(link); // Add link to queue
                visited.insert(link); // Mark link as visited
            }
        }
    }

    // Save content to file
    {
        std::lock_guard<std::mutex> lock(fileMutex); // Protect file writes
        std::ofstream outFile(outputFilePath, std::ios::app);
        if (!outFile) {
            std::cerr << "Error: Unable to open file " << outputFilePath << " for writing.\n";
            return;
        }
        outFile << "Crawled URL: " << url << "\nContent:\n" << response << "\n\n";
        std::cout << "Successfully wrote data for URL: " << url << "\n";
    }
}

// Start the crawling process
void Crawler::start() {
    const int numThreads = 4; // Number of threads
    std::vector<std::thread> threads;

    while (!urlQueue.empty()) {
        for (int i = 0; i < numThreads; ++i) {
            if (urlQueue.empty()) break; // Exit if queue is empty
            std::string url;
            {
                std::lock_guard<std::mutex> lock(queueMutex); // Protect queue access
                if (!urlQueue.empty()) {
                    url = urlQueue.front(); // Get the next URL
                    urlQueue.pop();        // Remove it from the queue
                }
            }
            if (!url.empty()) {
                threads.emplace_back(&Crawler::crawlUrl, this, url); // Start a thread
            }
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            if (thread.joinable()) thread.join();
        }
        threads.clear(); // Clear completed threads
    }
}
