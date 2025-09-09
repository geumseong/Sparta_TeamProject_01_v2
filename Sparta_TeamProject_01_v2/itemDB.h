#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Item.h"

/**
 * @class GameDB
 * @brief JSON 기반 게임 데이터베이스 로더 및 단순 출력 클래스
 */
inline E_Type stringToType(const std::string& str) {
    if (str == "Consumable") return E_Type::Consumable;
    if (str == "Equipment")  return E_Type::Equipment;
    if (str == "Accessory")  return E_Type::Accessory;
    if (str == "Material")   return E_Type::Material;
    return E_Type::Unknown1;
}

inline const char* typeToString(E_Type type) {
    switch (type) {
    case E_Type::Consumable: return "Consumable";
    case E_Type::Equipment:  return "Equipment";
    case E_Type::Accessory:  return "Accessory";
    case E_Type::Material:   return "Material";
    default: return "Unknown1";
    }
}


class ItemDB {
public:
    ItemDB() = default;

    /**
     * @brief JSON 파일 로드
     * @param path JSON 파일 경로
     * @param err 에러 메시지 출력용 (옵션)
     * @return 성공 여부
     */
    bool loadFromFile(const std::string& path, std::string* err = nullptr) {
        std::ifstream f(path);
        if (!f.is_open()) {
            if (err) *err = "파일을 열 수 없습니다: " + path;
            return false;
        }
        try {
            f >> db_;
        }
        catch (const std::exception& e) {
            if (err) *err = std::string("JSON 파싱 실패: ") + e.what();
            return false;
        }
        return true;
    }

    /**
     * @brief 전체 아이템 출력
     */
    void printAllItems() const {
        if (!db_.contains("items")) return;

        std::cout << "=== Items ===\n";
        for (auto it = db_["items"].begin(); it != db_["items"].end(); ++it) {
            std::cout << it.key()
                << " -> " << it.value().value("name", "UNKNOWN")
                << " (price: " << it.value().value("price", 0) << ")\n";
        }
    }


    unique_ptr<Item> findItemById(const string& itemId) const //id를 통해서 검색
    {
        if (!db_.contains("items")) return nullptr;

        auto it = db_["items"].find(itemId);
        if (it == db_["items"].end()) {
            return nullptr; // 해당 ID 없음
        }

        // 값 파싱
        string  name = it->value("name", string{});
        int     price = it->value("price", 0);
        int     count = 1;
        string  typeStr = it->value("type", string{ "Unknown" });
        E_Type  type = stringToType(typeStr);

        auto ptr = make_unique<Item>(name, price, count, type);
        // ID 저장하고 싶으면 여기서 추가
        // ptr->id = itemId;
        return ptr;
    }


    vector<Item> getShopTable(const std::string& shoptableName) const { // 상점 테이플 리턴
        vector<Item> list;
        if (!db_.contains("shopTables") || !db_.contains("items")) return list;

        auto it = db_["shopTables"].find(shoptableName);
        if (it == db_["shopTables"].end()) return list;

        for (auto& entry : *it)
        {
            string itemId = entry.value("itemId", "");
            auto item = db_["items"].find(itemId);
            if (item != db_["items"].end()) {
                string  name = item->value("name", string{});
                int     price = item->value("price", 0);
                int     count = 1;
                string  typeStr = item->value("type", string{ "Unknown" });
                E_Type  type = stringToType(typeStr);
                string  effecttype = item->value("effecttype", string{});

                auto ptr = Item(name, price, count, type);
                if (effecttype == "HealEffect")
                {
                    int hp = item->value("hp", 0);
                    int mp = item->value("mp", 0);
                    ptr.addEffect<HealEffect>(hp, mp);
                }
                else if (effecttype == "BuffEffect")
                {
                    int ab = item->value("ab", 0);
                    int db = item->value("db", 0);
                    int sb = item->value("sb", 0);
                    int hb = item->value("hb", 0);
                    int mb = item->value("mb", 0);
                    ptr.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                }
                else {}

                list.push_back(move(ptr));
            }
        }
        return list;
    }


    vector<vector<Item>> getRecipeTable(const std::string& recipetableName) const //레시피 리턴
    {                                                                             //recipetableName 물약, 장비 레시피 구분
        vector<vector<Item>> recipeList;
        vector<Item> inputList;
        vector<Item> outputList;
        if (!db_.contains("recipeTables") || !db_.contains("items")) return recipeList;

        auto it = db_["recipeTables"].find(recipetableName);
        if (it == db_["recipeTables"].end()) return recipeList;

        for (auto& recipe : *it)
        {
            for (auto& in : recipe["inputs"])
            {
                string itemId = in.value("itemId", "");
                auto item = db_["items"].find(itemId);
                if (item != db_["items"].end())
                {
                    string  name = item->value("name", string{});
                    int     price = item->value("price", 0);
                    int     count = 1;
                    string  typeStr = item->value("type", string{ "Unknown" });
                    E_Type  type = stringToType(typeStr);
                    string  effecttype = item->value("effecttype", string{});

                    auto ptr = Item(name, price, count, type);
                    if (effecttype == "HealEffect")
                    {
                        int hp = item->value("hp", 0);
                        int mp = item->value("mp", 0);
                        ptr.addEffect<HealEffect>(hp, mp);
                    }
                    else if (effecttype == "BuffEffect")
                    {
                        int ab = item->value("ab", 0);
                        int db = item->value("db", 0);
                        int sb = item->value("sb", 0);
                        int hb = item->value("hb", 0);
                        int mb = item->value("mb", 0);
                        ptr.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                    }

                    inputList.push_back(move(ptr));


                }
            }
            for (auto& in : recipe["outputs"])
            {
                string itemId = in.value("itemId", "");
                auto item = db_["items"].find(itemId);
                if (item != db_["items"].end())
                {
                    string  name = item->value("name", string{});
                    int     price = item->value("price", 0);
                    int     count = 1;
                    string  typeStr = item->value("type", string{ "Unknown" });
                    E_Type  type = stringToType(typeStr);
                    string  effecttype = item->value("effecttype", string{});

                    auto ptr = Item(name, price, count, type);
                    if (effecttype == "HealEffect")
                    {
                        int hp = item->value("hp", 0);
                        int mp = item->value("mp", 0);
                        ptr.addEffect<HealEffect>(hp, mp);
                    }
                    else if (effecttype == "BuffEffect")
                    {
                        int ab = item->value("ab", 0);
                        int db = item->value("db", 0);
                        int sb = item->value("sb", 0);
                        int hb = item->value("hb", 0);
                        int mb = item->value("mb", 0);
                        ptr.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                    }
                    else {}
                    outputList.push_back(move(ptr));

                }
            }
        }
        recipeList.push_back(move(outputList));
        recipeList.push_back(move(inputList));
        return recipeList;
    }



    /**
     * @brief 드랍 테이블 출력
     * @param monsterName 몬스터 이름
     */

    vector<Item> getDropTable(const std::string& monsterName) const {
        vector<Item> droplist;
        if (!db_.contains("dropTables") || !db_.contains("items")) return droplist;

        auto it = db_["dropTables"].find(monsterName);
        if (it == db_["dropTables"].end()) return droplist;

        for (auto& drop : *it)
        {
            string itemId = drop.value("itemId", "");
            auto item = db_["items"].find(itemId);
            if (item != db_["items"].end())
            {
                string  name = item->value("name", string{});
                int     price = item->value("price", 0);
                int     count = 1;
                string  typeStr = item->value("type", string{ "Unknown" });
                E_Type  type = stringToType(typeStr);
                string  effecttype = item->value("effecttype", string{});

                auto ptr = Item(name, price, count, type);
                if (effecttype == "HealEffect")
                {
                    int hp = item->value("hp", 0);
                    int mp = item->value("mp", 0);
                    ptr.addEffect<HealEffect>(hp, mp);
                }
                else if (effecttype == "BuffEffect")
                {
                    int ab = item->value("ab", 0);
                    int db = item->value("db", 0);
                    int sb = item->value("sb", 0);
                    int hb = item->value("hb", 0);
                    int mb = item->value("mb", 0);
                    ptr.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                }
                else {}

                droplist.push_back(move(ptr));
            }
        }
        return droplist;
    }



private:
    nlohmann::json db_; ///< JSON 전체 데이터
};
