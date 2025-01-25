#include <iostream>
#include "crawler.h"

int main() {
    // Seed URL for starting the crawler
    std::string seedUrl = "https://quotes.toscrape.com";

    // Initialize crawler
    Crawler crawler;
    crawler.addSeedUrl(seedUrl);

    // Start crawling
    crawler.start();

    std::cout << "Crawling completed. Data saved in 'data/output.json'./n";
    return 0;
}
