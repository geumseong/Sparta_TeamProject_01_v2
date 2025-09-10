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
    struct RecipeTable {
        std::vector<Item> outputs;                 // [ 레시피별 결과 아이템들... ]
        std::vector<std::vector<Item>> inputs;     // [ [레시피1 재료들...], [레시피2 재료들...] ... ]
    };

    RecipeTable getRecipeTable(const std::string& recipetableName) const
    {
        RecipeTable result;

        if (!db_.contains("recipeTables") || !db_.contains("items")) return result;

        auto it = db_["recipeTables"].find(recipetableName);
        if (it == db_["recipeTables"].end()) return result;

        for (auto& recipe : *it)
        {
            // 1) outputs: 보통 예시대로 1개지만 배열이므로 모두 처리
            for (auto& out : recipe["outputs"])
            {
                std::string itemId = out.value("itemId", "");
                int outCount = out.value("count", 1);

                auto itemIt = db_["items"].find(itemId);
                if (itemIt != db_["items"].end())
                {
                    std::string name = itemIt->value("name", std::string{});
                    int        price = itemIt->value("price", 0);
                    int        count = outCount; // 레시피에서 준 count 반영
                    std::string typeStr = itemIt->value("type", std::string{ "Unknown" });
                    E_Type     type = stringToType(typeStr);
                    std::string effecttype = itemIt->value("effecttype", std::string{});

                    Item outItem(name, price, count, type);
                    if (effecttype == "HealEffect")
                    {
                        int hp = itemIt->value("hp", 0);
                        int mp = itemIt->value("mp", 0);
                        outItem.addEffect<HealEffect>(hp, mp);
                    }
                    else if (effecttype == "BuffEffect")
                    {
                        int ab = itemIt->value("ab", 0);
                        int db = itemIt->value("db", 0);
                        int sb = itemIt->value("sb", 0);
                        int hb = itemIt->value("hb", 0);
                        int mb = itemIt->value("mb", 0);
                        outItem.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                    }
                    result.outputs.emplace_back(std::move(outItem));
                }
            }

            // 2) inputs: 이 레시피의 재료들을 한 벡터로 묶어 inputs에 push
            std::vector<Item> thisRecipeInputs;

            for (auto& in : recipe["inputs"])
            {
                std::string itemId = in.value("itemId", "");
                int inCount = in.value("count", 1);

                auto itemIt = db_["items"].find(itemId);
                if (itemIt != db_["items"].end())
                {
                    std::string name = itemIt->value("name", std::string{});
                    int        price = itemIt->value("price", 0);
                    int        count = inCount; // 레시피에서 준 count 반영
                    std::string typeStr = itemIt->value("type", std::string{ "Unknown" });
                    E_Type     type = stringToType(typeStr);
                    std::string effecttype = itemIt->value("effecttype", std::string{});

                    Item inItem(name, price, count, type);
                    if (effecttype == "HealEffect")
                    {
                        int hp = itemIt->value("hp", 0);
                        int mp = itemIt->value("mp", 0);
                        inItem.addEffect<HealEffect>(hp, mp);
                    }
                    else if (effecttype == "BuffEffect")
                    {
                        int ab = itemIt->value("ab", 0);
                        int db = itemIt->value("db", 0);
                        int sb = itemIt->value("sb", 0);
                        int hb = itemIt->value("hb", 0);
                        int mb = itemIt->value("mb", 0);
                        inItem.addEffect<BuffEffect>(ab, db, sb, hb, mb);
                    }

                    thisRecipeInputs.emplace_back(std::move(inItem));
                }
            }

            result.inputs.emplace_back(std::move(thisRecipeInputs));
        }

        return result;
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
