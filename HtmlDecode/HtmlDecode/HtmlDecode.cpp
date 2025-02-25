#include <iostream>
#include <string>

std::string HtmlDecode(const std::string& html) {
    std::string result;
    result.reserve(html.size());

    size_t pos = 0;
    while (pos < html.size()) {
        size_t ampPos = html.find('&', pos);
        if (ampPos == std::string::npos) {
            result.append(html, pos, html.size() - pos);
            break;
        }
        result.append(html, pos, ampPos - pos);

        size_t semicolonPos = html.find(';', ampPos);
        if (semicolonPos != std::string::npos) {
            std::string entity = html.substr(ampPos, semicolonPos - ampPos + 1);
            if (entity == "&quot;") result += '"';
            else if (entity == "&apos;") result += '\'';
            else if (entity == "&lt;") result += '<';
            else if (entity == "&gt;") result += '>';
            else if (entity == "&amp;") result += '&';
            else {
                result.append(entity);
            }
            pos = semicolonPos + 1;
            continue;
        }
        result += '&';
        pos = ampPos + 1;
    }
    return result;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) 
        {
            break;
        }
        std::cout << HtmlDecode(line) << std::endl;
    }
    return 0;
}
