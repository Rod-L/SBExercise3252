#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "StrExtra.h"

using namespace nlohmann;

void make_records() {
    json entries;
    json entry;

    ////  Mr. Nobody

    entry["Name"]           = "Mr. Nobody";
    entry["ReleaseYear"]    = 2009;
    entry["Countries"]      = split_str("Belgium, Germany, Canada, France, UK, Luxembourg, USA");
    entry["Genre"]          = split_str("science fiction, melodrama, fantasy, drama");
    entry["Directors"]      = split_str("Jaco van Dormael");
    entry["Screenwriters"]  = split_str("Jaco van Dormael");
    entry["Studios"]        = split_str(
            "Antenne-2 (A2), Belgium Film Fund, Canal+ [fr], Caviar, Christal Films, Climax Films, Degeto Film,"
            "Fortis Film Fund, France 2 Cinéma, France 3 (FR 3), France 3 Cinéma, Integral Films, Lago Film,"
            "Medienboard Berlin-Brandenburg, Poisson Rouge Pictures, RTL-TVi, Scope Pictures, Studio Babelsberg,"
            "Toto & Co Films, Wild Bunch");
    entry["Producers"]      = split_str("Philippe Godeau, Jean-Yves Asselin, Nathalie Gastaldo");
    entry["Actors"]         = json({{"Jared Leto", "Nemo Adult / Old Nemo"}, {"Sarah Polley", "Adult Elise"}, {"Diane Kruger", "Anna Adult"}, {"Phạm Linh", "Adult Jean"}}); // actor name - role
    entries[entry["Name"]] = entry;

    ////  Habemus Papam

    entry["Name"]           = "Habemus Papam";
    entry["ReleaseYear"]    = 2011;
    entry["Countries"]      = split_str("Italy, France");
    entry["Genre"]          = split_str("comedy, drama");
    entry["Directors"]      = split_str("Nanni Moretti");
    entry["Studios"]        = split_str("Backup Films, Canal+ [fr], Coficup, Eurimages, Le Pacte, Rai Cinema, Sacher Film");
    entry["Screenwriters"]  = split_str("Nanni Moretti, Francesco Piccolo, Federica Pontremoli, Tom King");
    entry["Producers"]      = split_str("Jean Labadie, Nanni Moretti, Domenico Procacci");
    entry["Actors"]         = json({{"Michel Piccoli", "Papa"}, {"Jerzy Stuhr", "portavoce"}, {"Renato Scarpa", "Cardinal Gregori"}, {"Franco Graziosi", "Cardinal Bollati"}}); // actor name - role
    entries[entry["Name"]] = entry;

    ////  Праздник святого Иоргена

    entry["Name"]           = "Праздник святого Иоргена";
    entry["ReleaseYear"]    = 1930;
    entry["Countries"]      = split_str("СССР");
    entry["Genre"]          = split_str("comedy");
    entry["Directors"]      = split_str("Яков Протазанов");
    entry["Screenwriters"]  = split_str("Яков Протазанов, Владимир Швейцер, Харальд Бергстедт");
    entry["Studios"]        = split_str("Backup Films, Canal+ [fr], Coficup, Eurimages, Le Pacte, Rai Cinema, Sacher Film");
    entry["Producers"]      = json::array({});
    entry["Actors"]         = json({{"Игорь Ильинский", "Франц Щульц"}, {"Анатолий Кторов", "Коркис"}, {"Мария Стрелкова", "Олеандра"}, {"Михаил Климов", "наместник храма"}}); // actor name - role
    entries[entry["Name"]] = entry;

    //// Бен Гур

    entry["Name"]           = "Ben-Hur";
    entry["ReleaseYear"]    = 1959;
    entry["Countries"]      = split_str("USA");
    entry["Genre"]          = split_str("drama, history, adventure");
    entry["Directors"]      = split_str("William Wyler");
    entry["Screenwriters"]  = split_str("Lew Wallace, Karl Tunberg, Gore Vidal, Maxwell Anderson, S.N. Behrman");
    entry["Studios"]        = split_str("Metro-Goldwyn-Mayer (MGM)");
    entry["Producers"]      = split_str("Sam Zimbalist, Sol C. Siegel, Joseph Vogel");
    entry["Actors"]         = json({{"Charlton Heston", "Judah Ben-Hur"}, {"Jack Hawkins", "Quintus Arrius"}, {"Haya Harareet", "Esther"}, {"Stephen Boyd", "Messala"}}); // actor name - role
    entries[entry["Name"]] = entry;

    //// Римские каникулы

    entry["Name"]           = "Roman Holiday";
    entry["ReleaseYear"]    = 1953;
    entry["Countries"]      = split_str("USA");
    entry["Genre"]          = split_str("drama, comedy");
    entry["Directors"]      = split_str("William Wyler");
    entry["Screenwriters"]  = split_str("John Dighton, Dalton Trumbo, Ian McLellan Hunter");
    entry["Studios"]        = split_str("Paramount Pictures");
    entry["Producers"]      = split_str("Lester Koenig, Robert Wyler, William Wyler");
    entry["Actors"]         = json({{"Gregory Peck", "Joe Bradley"}, {"Audrey Hepburn", "Princess Ann"}, {"Eddie Albert", "Irving Radovich"}, {"Hartley Power", "Mr. Hennessy"}}); // actor name - role
    entries[entry["Name"]] = entry;

    std::ofstream ofile("movie_records.json");
    if (ofile.is_open()) {
        ofile << entries.dump(1, '\t');
    } else {
        std::cout << "Could not create file 'movie_records.json'.";
        return;
    }
}

int main() {
    std::ifstream file("movie_records.json");
    if (!file.is_open()) {
        make_records();
        file.open("movie_records.json");
        if (!file.is_open()) return 0;
    }

    json entries = json::parse(file);

    std::cout << "Enter name of actor you want to know about:" << std::endl;
    std::string name;
    std::getline(std::cin, name);

    bool have_any = false;
    for (auto& entry : entries) {
        auto actors = entry["Actors"];
        auto it = actors.find(name);
        if (it != actors.end()) {
            std::cout << "Movie: " << entry["Name"] << ", role: " << actors[name] << std::endl;
            have_any = true;
        }
    }

    if (!have_any) std::cout << "No info about '" << name << "' in database." << std::endl;
}