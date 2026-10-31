#include "HerbsRepository.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

HerbsRepository::HerbsRepository() {
    auto data = DataLoader::LoadFromFile("herbs.txt");
    data_ = std::move(data);
}

int HerbsRepository::GetAvailableQuantity(const std::string& herbType) const {
    auto it = data_.find(herbType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }
    return std::stoi(it->second[0]);
}

void HerbsRepository::UpdateQuantity(const std::string& herbType, int newQuantity) {
    auto it = data_.find(herbType);

    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de hierba desconocido: " + herbType);
    }

    it->second[0] = std::to_string(newQuantity);

    std::ofstream out("Data/herbs.txt");

    if (!out) {
        throw std::runtime_error("No se puede guardar el archivo herbs.txt");
    }

    for (const auto& herb : data_) {
        out << herb.first << ": ";

        for (size_t i = 0; i < herb.second.size(); ++i) {
            if (i > 0) out << ", ";
            out << herb.second[i];
        }

        out << "\n";
    }
}