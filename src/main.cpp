#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
  std::string* str = (std::string*)userp;
  str->append((char*)contents, size * nmemb);
  return size * nmemb;
}

int main() {
  std::string response; 
  CURL* curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "api.kanye.rest");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
  }

  response.erase(0,9);
  response.erase(response.length() -1, response.length());
  std::cout << response << " - Kanye West" << std::endl;

  return 0;
}

