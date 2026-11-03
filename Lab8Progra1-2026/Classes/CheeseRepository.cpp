#include "CheeseRepository.h"
#include <stdexcept>
#include <fstream>

CheeseRepository::CheeseRepository() {
    auto data = DataLoader::LoadFromFile("cheese.txt");
    data_ = std::move(data);
}

int CheeseRepository::GetAvailableQuantity(const std::string& cheeseType) const {
    auto it = data_.find(cheeseType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de queso desconocido: " + cheeseType);
    }
    return std::stoi(it->second[0]);
}

void CheeseRepository::UpdateQuantity(const std::string& cheeseType, int newQuantity) {
    auto it = data_.find(cheeseType);
    if (it == data_.end()) {
        throw std::invalid_argument("Tipo de queso desconocido: " + cheeseType);
    }

    // Actualiza el valor en memoria
    it->second[0] = std::to_string(newQuantity);

    // Guarda los cambios en el archivo de texto
    std::ofstream out("cheese.txt");
    if (!out) {
        throw std::runtime_error("No se puede guardar el archivo cheese.txt");
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