#include <iostream>
#include <memory>
#include "include/array.h"
#include "include/figure.h"
#include "include/point.h"
#include "include/polygon.h"

void menu() {
    std::cout << "\n==== Лабораторная №4 (ООП) ====\n";
    std::cout << "1 - Добавить фигуру\n";
    std::cout << "2 - Удалить фигуру\n";
    std::cout << "3 - Показать все фигуры\n";
    std::cout << "4 - Общая площадь\n";
    std::cout << "0 - Выход\n";
    std::cout << "Выбор: ";
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;

    do {
        menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Выберите тип фигуры:\n";
                std::cout << "1 - Пятиугольник\n";
                std::cout << "2 - Шестиугольник\n";
                std::cout << "3 - Восьмиугольник\n";
                int type;
                std::cin >> type;

                std::shared_ptr<Figure<double>> fig;

                try {
                    switch (type) {
                        case 1: {
                            auto p = std::make_shared<Pentagon<double>>();
                            p->input();
                            fig = p;
                            break;
                        }
                        case 2: {
                            auto p = std::make_shared<Hexagon<double>>();
                            p->input();
                            fig = p;
                            break;
                        }
                        case 3: {
                            auto p = std::make_shared<Octagon<double>>();
                            p->input();
                            fig = p;
                            break;
                        }
                        default:
                            std::cout << "Неверный выбор!\n";
                            continue;
                    }

                    figures.push_back(fig);
                    std::cout << "Фигура добавлена.\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка при создании фигуры: " << e.what() << "\n";
                }
                break;
            }

            case 2: {
                size_t index;
                std::cout << "Введите индекс фигуры для удаления: ";
                std::cin >> index;
                try {
                    
                    figures.remove(index);
                    std::cout << "Фигура удалена.\n";
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }

            case 3: {
                if (figures.size() == 0) {
                    std::cout << "Список фигур пуст.\n";
                    break;
                }
                for (size_t i = 0; i < figures.size(); ++i) {
                    std::cout << "\nФигура [" << i << "]:\n";
                    figures[i]->print();

                    std::cout << "Площадь: " << figures[i]->area() << "\n";
                    std::cout << "Центр: ";
                    figures[i]->center().print();
                    std::cout << "\n";
                }
                break;
            }

            case 4: {
                double total = figures.totalArea();

                std::cout << "Общая площадь: " << total << "\n";
                break;
            }

            case 0:
                std::cout << "Программа завершена.\n";
                break;   

            default:
                std::cout << "Неверный выбор!\n";

                break;
        }

    } while (choice != 0);

    return 0;
}
