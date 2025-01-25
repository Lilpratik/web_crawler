#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <queue>
#include <unordered_set>
#include <mutex>
#include <thread>

class Crawler {
private:
    std::queue<std::string> urlQueue;           // Queue for URLs to crawl
    std::unordered_set<std::string> visited;   // Set of visited URLs
    std::string outputFilePath;                // Path to save output
    std::mutex queueMutex;                     // Mutex for queue synchronization
    std::mutex fileMutex;                      // Mutex for file synchronization

public:
    Crawler();                                 // Constructor
    void addSeedUrl(const std::string& url);   // Add a seed URL to the queue
    void crawlUrl(const std::string& url);     // Crawl a single URL
    void start();                              // Start the crawling process
};

#endif // CRAWLER_H
