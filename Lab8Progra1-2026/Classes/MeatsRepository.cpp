#include "MeatsRepository.h"
#include <stdexcept>
#include <fstream>

MeatsRepository::MeatsRepository() {
    auto data = DataLoader::LoadFromFile("meats.txt");
    data_ = std::move(data);
}

int MeatsRepository::GetAvailableQuantity(const std::string& meatType) const {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }
    return std::stoi(it->second[0]);
}

void MeatsRepository::UpdateQuantity(const std::string& meatType, int newQuantity) {
    auto it = data_.find(meatType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de carne desconocido: " + meatType);
    }

    it->second[0] = std::to_string(newQuantity);

    std::ofstream out("meats.txt");
    if (!out) {
        throw std::runtime_error("No se puede guardar el archivo meats.txt");
    }

    for (const auto& item : data_) {
        out << item.first << ": ";
        for (size_t i = 0; i < item.second.size(); ++i) {
            if (i > 0) out << ", ";
            out << item.second[i];
        }
        out << "\n";
    }
}
