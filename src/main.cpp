#include <iostream>
#include "CsvFile.h"
#include "BinFile.h"
#include "Review.h"
#include "Tester.h"

int menu(int argc, char* argv[]) {
    try {
        Tester tester(argc, argv);

        while (true) {
            std::cout << "\nMenu Principal\n"
                    << "1. Acessar uma avaliacao especifica\n"
                    << "2. Acessar N avaliacoes aleatorias\n"
                    << "3. Ordenar avaliacoes\n"
                    << "4. Contar versoes do aplicativo\n"
                    << "5. Comparar estruturas de dados Arvore B e Arvore Vermelha e Preta\n"
                    << "6. Comprimir N review_texts aleatorios\n"
                    << "7. Descomprimir arquivo reviewsComp.bin\n"
                    << "8. Executar sequencia de compressoes Huffman\n"
                    << "9. Sair\n"
                    << "Escolha uma opcao: ";

            switch (getUserInputFromConsole<int>("")) {
                case 1:
                    tester.accessReview();
                    break;
                case 2:
                    tester.accessNRandomReviews();
                    break;
                case 3:
                    tester.sortReviews();
                    break;
                case 4:
                    tester.countAppVersions();
                    break;
                case 5:
                    tester.compareDataStructures();
                    break;
                case 6:
                    tester.compressRandomReviews();
                    break;
                case 7:
                    tester.decompressReviews();
                    break;
                case 8:
                    tester.runCompressionSequence();
                    break;
                case 9:
                    std::cout << "Encerrando o programa.\n";
                    return 0;
                default:
                    std::cout << "Opção invalida. Tente novamente.\n";
                    break;
            }
        }
    }
    catch (const std::exception&e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }
}

// run: ./exec <input_file> <output_file>
// csvFile file expected: tiktok_app_reviews.csv
// get in https://www.kaggle.com/datasets/shivamb/35-million-tiktok-mobile-app-reviews
// i.e. ./exec ../tiktok_app_reviews.csv ../out2.bin
int main(int argc, char* argv[]) {
    return menu(argc, argv);

    //    read the csv file and return a vector of reviews
    CsvFile csvFile(argc, argv);
    auto reviews = csvFile.read();

    //    write the vector of reviews in a binary file
    BinFile binFile(argc, argv);
    binFile.write(std::move(reviews));
    reviews.reset();

    //    read the binary file and return a vector of reviews
    //    auto result = binFile.read();
    //    result.reset();

    Tester tester(argc, argv);
    //    tester.accessReview();
    //    tester.accessNRandomReviews();
    tester.sortReviews();

    return 0;
}
