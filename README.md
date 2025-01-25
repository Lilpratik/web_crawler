# Web Crawler

A simple and efficient web crawler that extracts data from websites and saves it in a structured format. This project is designed for educational purposes to demonstrate web scraping, data extraction, and multithreading in C++.

## Features

- **Multithreaded crawling**: Uses multiple threads to crawl URLs concurrently for faster processing.
- **Web scraping**: Extracts links from web pages and saves content.
- **File output**: Saves crawled data in a `data/output.json` file for easy access and analysis.
- **cURL & Gumbo**: Utilizes cURL for making HTTP requests and Gumbo for parsing HTML.

## Technologies Used

- **C++**: The main programming language.
- **cURL**: A library for making HTTP requests.
- **Gumbo**: A HTML5 parser used to extract links.
- **Threads**: For concurrent URL crawling.

## How to Use

### Prerequisites
Before running the web crawler, ensure you have the following installed on your system:

- **C++ compiler** (with C++17 support)
- **CMake** (for building the project)
- **cURL** library
- **Gumbo** library

### Steps to Run

1. Clone this repository:

   ```bash
   git clone https://github.com/Lilpratik/web_crawler.git
   cd web_crawler
2. Create a build directory and compile the project:

   ```bash
    mkdir build
    cd build
    cmake ..
    make
3. Run the program:
   ```bash
   ./web_crawler
4. The program will crawl the seed URL, extract links, and save the crawled content in data/output.json.

## Contributing
Contributions are welcome! If you want to add features or improve the code, feel free to fork the repository, create a branch, and submit a pull request.

Fork the repository.
Create your feature branch (git checkout -b feature/your-feature).
Commit your changes (git commit -m 'Add new feature').
Push to the branch (git push origin feature/your-feature).
Create a new pull request.

## ⭐ Star this Repository
If you find this project useful or interesting, please consider giving it a star! ⭐
## Happy crawling! 🌐
