#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_2119(Table &tbl_SerializeFromObject_TD_3934_input, Table &tbl_Filter_TD_2119_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((p_size#289 >= 1) AND (((((p_brand#287 = Brand#51) AND p_container#290 IN (SM CASE,SM BOX,SM PACK,SM PKG)) AND (p_size#289 <= 5)) OR (((p_brand#287 = Brand#32) AND p_container#290 IN (MED BAG,MED BOX,MED PKG,MED PACK)) AND (p_size#289 <= 10))) OR (((p_brand#287 = Brand#12) AND p_container#290 IN (LG CASE,LG BOX,LG PACK,LG PKG)) AND (p_size#289 <= 15)))))
    // Input: ListBuffer(p_partkey#284, p_brand#287, p_size#289, p_container#290)
    // Output: ListBuffer(p_partkey#284, p_brand#287, p_size#289, p_container#290)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_3934_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _p_size289 = tbl_SerializeFromObject_TD_3934_input.getInt32(i, 2);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287 = tbl_SerializeFromObject_TD_3934_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290 = tbl_SerializeFromObject_TD_3934_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 3);
        auto reuse_col_str_576 = std::string(_p_container290.data());
        auto reuse_col_str_715 = std::string(_p_container290.data());
        auto reuse_col_str_598 = std::string(_p_container290.data());
        if ((_p_size289 >= 1) && (((((std::string(_p_brand287.data()) == "Brand#51") && ((reuse_col_str_576 == "SM CASE") || (reuse_col_str_576 == "SM BOX") || (reuse_col_str_576 == "SM PACK") || (reuse_col_str_576 == "SM PKG") || (0))) && (_p_size289 <= 5)) || (((std::string(_p_brand287.data()) == "Brand#32") && ((reuse_col_str_715 == "MED BAG") || (reuse_col_str_715 == "MED BOX") || (reuse_col_str_715 == "MED PKG") || (reuse_col_str_715 == "MED PACK") || (0))) && (_p_size289 <= 10))) || (((std::string(_p_brand287.data()) == "Brand#12") && ((reuse_col_str_598 == "LG CASE") || (reuse_col_str_598 == "LG BOX") || (reuse_col_str_598 == "LG PACK") || (reuse_col_str_598 == "LG PKG") || (0))) && (_p_size289 <= 15)))) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_3934_input.getInt32(i, 0);
            tbl_Filter_TD_2119_output.setInt32(r, 0, _p_partkey284_t);
            std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287_t = tbl_SerializeFromObject_TD_3934_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            tbl_Filter_TD_2119_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _p_brand287_t);
            int32_t _p_size289_t = tbl_SerializeFromObject_TD_3934_input.getInt32(i, 2);
            tbl_Filter_TD_2119_output.setInt32(r, 2, _p_size289_t);
            std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290_t = tbl_SerializeFromObject_TD_3934_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 3);
            tbl_Filter_TD_2119_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 3, _p_container290_t);
            r++;
        }
    }
    tbl_Filter_TD_2119_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_2119_output #Row: " << tbl_Filter_TD_2119_output.getNumRow() << std::endl;
}

void SW_Filter_TD_2442(Table &tbl_SerializeFromObject_TD_3900_input, Table &tbl_Filter_TD_2442_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((isnotnull(l_shipinstruct#63) AND (l_shipmode#64 IN (AIR,AIR REG) AND (l_shipinstruct#63 = DELIVER IN PERSON))) AND ((((l_quantity#54 >= 7) AND (l_quantity#54 <= 17)) OR ((l_quantity#54 >= 10) AND (l_quantity#54 <= 20))) OR ((l_quantity#54 >= 24) AND (l_quantity#54 <= 34)))))
    // Input: ListBuffer(l_partkey#51, l_quantity#54, l_extendedprice#55, l_discount#56, l_shipinstruct#63, l_shipmode#64)
    // Output: ListBuffer(l_partkey#51, l_quantity#54, l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_3900_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipinstruct63 = tbl_SerializeFromObject_TD_3900_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 4);
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64 = tbl_SerializeFromObject_TD_3900_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 5);
        int32_t _l_quantity54 = tbl_SerializeFromObject_TD_3900_input.getInt32(i, 1);
        auto reuse_col_str_708 = std::string(_l_shipmode64.data());
        if (((1) && (((reuse_col_str_708 == "AIR") || (reuse_col_str_708 == "AIR REG") || (0)) && (std::string(_l_shipinstruct63.data()) == "DELIVER IN PERSON"))) && ((((_l_quantity54 >= 7) && (_l_quantity54 <= 17)) || ((_l_quantity54 >= 10) && (_l_quantity54 <= 20))) || ((_l_quantity54 >= 24) && (_l_quantity54 <= 34)))) {
            int32_t _l_partkey51_t = tbl_SerializeFromObject_TD_3900_input.getInt32(i, 0);
            tbl_Filter_TD_2442_output.setInt32(r, 0, _l_partkey51_t);
            int32_t _l_quantity54_t = tbl_SerializeFromObject_TD_3900_input.getInt32(i, 1);
            tbl_Filter_TD_2442_output.setInt32(r, 1, _l_quantity54_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_3900_input.getInt32(i, 2);
            tbl_Filter_TD_2442_output.setInt32(r, 2, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_3900_input.getInt32(i, 3);
            tbl_Filter_TD_2442_output.setInt32(r, 3, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_2442_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_2442_output #Row: " << tbl_Filter_TD_2442_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_1149_key_leftMajor {
    int32_t _l_partkey51;
    bool operator==(const SW_JOIN_INNER_TD_1149_key_leftMajor& other) const {
        return ((_l_partkey51 == other._l_partkey51));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1149_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1149_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._l_partkey51));
    }
};
}
struct SW_JOIN_INNER_TD_1149_payload_leftMajor {
    int32_t _l_partkey51;
    int32_t _l_quantity54;
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
};
struct SW_JOIN_INNER_TD_1149_key_rightMajor {
    int32_t _p_partkey284;
    bool operator==(const SW_JOIN_INNER_TD_1149_key_rightMajor& other) const {
        return ((_p_partkey284 == other._p_partkey284));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1149_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1149_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._p_partkey284));
    }
};
}
struct SW_JOIN_INNER_TD_1149_payload_rightMajor {
    int32_t _p_partkey284;
    std::string _p_brand287;
    int32_t _p_size289;
    std::string _p_container290;
};
void SW_JOIN_INNER_TD_1149(Table &tbl_Filter_TD_2442_output, Table &tbl_Filter_TD_2119_output, Table &tbl_JOIN_INNER_TD_1149_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer(((p_partkey#284 = l_partkey#51) AND (((((((p_brand#287 = Brand#51) AND p_container#290 IN (SM CASE,SM BOX,SM PACK,SM PKG)) AND (l_quantity#54 >= 7)) AND (l_quantity#54 <= 17)) AND (p_size#289 <= 5)) OR (((((p_brand#287 = Brand#32) AND p_container#290 IN (MED BAG,MED BOX,MED PKG,MED PACK)) AND (l_quantity#54 >= 10)) AND (l_quantity#54 <= 20)) AND (p_size#289 <= 10))) OR (((((p_brand#287 = Brand#12) AND p_container#290 IN (LG CASE,LG BOX,LG PACK,LG PKG)) AND (l_quantity#54 >= 24)) AND (l_quantity#54 <= 34)) AND (p_size#289 <= 15)))))
    // Left Table: ListBuffer(l_partkey#51, l_quantity#54, l_extendedprice#55, l_discount#56)
    // Right Table: ListBuffer(p_partkey#284, p_brand#287, p_size#289, p_container#290)
    // Output Table: ListBuffer(l_extendedprice#55, l_discount#56)
    int left_nrow = tbl_Filter_TD_2442_output.getNumRow();
    int right_nrow = tbl_Filter_TD_2119_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1149_key_leftMajor, SW_JOIN_INNER_TD_1149_payload_leftMajor> ht1;
        int nrow1 = tbl_Filter_TD_2442_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _l_partkey51_k = tbl_Filter_TD_2442_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_1149_key_leftMajor keyA{_l_partkey51_k};
            int32_t _l_partkey51 = tbl_Filter_TD_2442_output.getInt32(i, 0);
            int32_t _l_quantity54 = tbl_Filter_TD_2442_output.getInt32(i, 1);
            int32_t _l_extendedprice55 = tbl_Filter_TD_2442_output.getInt32(i, 2);
            int32_t _l_discount56 = tbl_Filter_TD_2442_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_1149_payload_leftMajor payloadA{_l_partkey51, _l_quantity54, _l_extendedprice55, _l_discount56};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_2119_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _p_partkey284_k = tbl_Filter_TD_2119_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1149_key_leftMajor{_p_partkey284_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_partkey51 = (it->second)._l_partkey51;
                int32_t _l_quantity54 = (it->second)._l_quantity54;
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _p_partkey284 = tbl_Filter_TD_2119_output.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287_n = tbl_Filter_TD_2119_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _p_brand287 = std::string(_p_brand287_n.data());
                int32_t _p_size289 = tbl_Filter_TD_2119_output.getInt32(i, 2);
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290_n = tbl_Filter_TD_2119_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 3);
                std::string _p_container290 = std::string(_p_container290_n.data());
                if (((((((_p_brand287 == "Brand#51") && ((_p_container290 == "SM CASE") || (_p_container290 == "SM BOX") || (_p_container290 == "SM PACK") || (_p_container290 == "SM PKG") || (0))) && (_l_quantity54 >= 7)) && (_l_quantity54 <= 17)) && (_p_size289 <= 5)) || (((((_p_brand287 == "Brand#32") && ((_p_container290 == "MED BAG") || (_p_container290 == "MED BOX") || (_p_container290 == "MED PKG") || (_p_container290 == "MED PACK") || (0))) && (_l_quantity54 >= 10)) && (_l_quantity54 <= 20)) && (_p_size289 <= 10))) || (((((_p_brand287 == "Brand#12") && ((_p_container290 == "LG CASE") || (_p_container290 == "LG BOX") || (_p_container290 == "LG PACK") || (_p_container290 == "LG PKG") || (0))) && (_l_quantity54 >= 24)) && (_l_quantity54 <= 34)) && (_p_size289 <= 15))) {
                    tbl_JOIN_INNER_TD_1149_output.setInt32(r, 0, _l_extendedprice55);
                    tbl_JOIN_INNER_TD_1149_output.setInt32(r, 1, _l_discount56);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_1149_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1149_key_rightMajor, SW_JOIN_INNER_TD_1149_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_2119_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _p_partkey284_k = tbl_Filter_TD_2119_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_1149_key_rightMajor keyA{_p_partkey284_k};
            int32_t _p_partkey284 = tbl_Filter_TD_2119_output.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287_n = tbl_Filter_TD_2119_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _p_brand287 = std::string(_p_brand287_n.data());
            int32_t _p_size289 = tbl_Filter_TD_2119_output.getInt32(i, 2);
            std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290_n = tbl_Filter_TD_2119_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 3);
            std::string _p_container290 = std::string(_p_container290_n.data());
            SW_JOIN_INNER_TD_1149_payload_rightMajor payloadA{_p_partkey284, _p_brand287, _p_size289, _p_container290};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_2442_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _l_partkey51_k = tbl_Filter_TD_2442_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1149_key_rightMajor{_l_partkey51_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                std::string _p_brand287 = (it->second)._p_brand287;
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287_n{};
                memcpy(_p_brand287_n.data(), (_p_brand287).data(), (_p_brand287).length());
                int32_t _p_size289 = (it->second)._p_size289;
                std::string _p_container290 = (it->second)._p_container290;
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290_n{};
                memcpy(_p_container290_n.data(), (_p_container290).data(), (_p_container290).length());
                int32_t _l_partkey51 = tbl_Filter_TD_2442_output.getInt32(i, 0);
                int32_t _l_quantity54 = tbl_Filter_TD_2442_output.getInt32(i, 1);
                int32_t _l_extendedprice55 = tbl_Filter_TD_2442_output.getInt32(i, 2);
                int32_t _l_discount56 = tbl_Filter_TD_2442_output.getInt32(i, 3);
                if (((((((_p_brand287 == "Brand#51") && ((_p_container290 == "SM CASE") || (_p_container290 == "SM BOX") || (_p_container290 == "SM PACK") || (_p_container290 == "SM PKG") || (0))) && (_l_quantity54 >= 7)) && (_l_quantity54 <= 17)) && (_p_size289 <= 5)) || (((((_p_brand287 == "Brand#32") && ((_p_container290 == "MED BAG") || (_p_container290 == "MED BOX") || (_p_container290 == "MED PKG") || (_p_container290 == "MED PACK") || (0))) && (_l_quantity54 >= 10)) && (_l_quantity54 <= 20)) && (_p_size289 <= 10))) || (((((_p_brand287 == "Brand#12") && ((_p_container290 == "LG CASE") || (_p_container290 == "LG BOX") || (_p_container290 == "LG PACK") || (_p_container290 == "LG PKG") || (0))) && (_l_quantity54 >= 24)) && (_l_quantity54 <= 34)) && (_p_size289 <= 15))) {
                    tbl_JOIN_INNER_TD_1149_output.setInt32(r, 0, _l_extendedprice55);
                    tbl_JOIN_INNER_TD_1149_output.setInt32(r, 1, _l_discount56);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_1149_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_1149_output #Row: " << tbl_JOIN_INNER_TD_1149_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_053(Table &tbl_JOIN_INNER_TD_1149_output, Table &tbl_Aggregate_TD_053_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(sum((l_extendedprice#55 * (100 - l_discount#56))) AS revenue#2068L)
    // Input: ListBuffer(l_extendedprice#55, l_discount#56)
    // Output: ListBuffer(revenue#2068L)
    int64_t sum_0 = 0;
    int nrow1 = tbl_JOIN_INNER_TD_1149_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_1149_output.getInt32(i, 0);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_1149_output.getInt32(i, 1);
        int64_t _revenue2068L_sum_0 = (_l_extendedprice55 * (100 - _l_discount56));
        sum_0 += _revenue2068L_sum_0;
    }
    int r = 0;
    int64_t _revenue2068L = sum_0;
    tbl_Aggregate_TD_053_output.setInt64(r++, 0, _revenue2068L);
    tbl_Aggregate_TD_053_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_053_output #Row: " << tbl_Aggregate_TD_053_output.getNumRow() << std::endl;
}

