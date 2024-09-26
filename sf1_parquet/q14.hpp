#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_244(Table &tbl_SerializeFromObject_TD_3370_input, Table &tbl_Filter_TD_244_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((l_shipdate#60 >= 19970301) AND (l_shipdate#60 < 19970401)))
    // Input: ListBuffer(l_partkey#51, l_extendedprice#55, l_discount#56, l_shipdate#60)
    // Output: ListBuffer(l_partkey#51, l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_3370_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_3370_input.getInt32(i, 3);
        if ((_l_shipdate60 >= 19970301) && (_l_shipdate60 < 19970401)) {
            int32_t _l_partkey51_t = tbl_SerializeFromObject_TD_3370_input.getInt32(i, 0);
            tbl_Filter_TD_244_output.setInt32(r, 0, _l_partkey51_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_3370_input.getInt32(i, 1);
            tbl_Filter_TD_244_output.setInt32(r, 1, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_3370_input.getInt32(i, 2);
            tbl_Filter_TD_244_output.setInt32(r, 2, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_244_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_244_output #Row: " << tbl_Filter_TD_244_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_1915_key_leftMajor {
    int32_t _l_partkey51;
    bool operator==(const SW_JOIN_INNER_TD_1915_key_leftMajor& other) const {
        return ((_l_partkey51 == other._l_partkey51));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1915_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1915_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._l_partkey51));
    }
};
}
struct SW_JOIN_INNER_TD_1915_payload_leftMajor {
    int32_t _l_partkey51;
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
};
struct SW_JOIN_INNER_TD_1915_key_rightMajor {
    int32_t _p_partkey284;
    bool operator==(const SW_JOIN_INNER_TD_1915_key_rightMajor& other) const {
        return ((_p_partkey284 == other._p_partkey284));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1915_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1915_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._p_partkey284));
    }
};
}
struct SW_JOIN_INNER_TD_1915_payload_rightMajor {
    int32_t _p_partkey284;
    std::string _p_type288;
};
void SW_JOIN_INNER_TD_1915(Table &tbl_Filter_TD_244_output, Table &tbl_SerializeFromObject_TD_2591_input, Table &tbl_JOIN_INNER_TD_1915_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((l_partkey#51 = p_partkey#284))
    // Left Table: ListBuffer(l_partkey#51, l_extendedprice#55, l_discount#56)
    // Right Table: ListBuffer(p_partkey#284, p_type#288)
    // Output Table: ListBuffer(l_extendedprice#55, l_discount#56, p_type#288)
    int left_nrow = tbl_Filter_TD_244_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_2591_input.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1915_key_leftMajor, SW_JOIN_INNER_TD_1915_payload_leftMajor> ht1;
        int nrow1 = tbl_Filter_TD_244_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _l_partkey51_k = tbl_Filter_TD_244_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_1915_key_leftMajor keyA{_l_partkey51_k};
            int32_t _l_partkey51 = tbl_Filter_TD_244_output.getInt32(i, 0);
            int32_t _l_extendedprice55 = tbl_Filter_TD_244_output.getInt32(i, 1);
            int32_t _l_discount56 = tbl_Filter_TD_244_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_1915_payload_leftMajor payloadA{_l_partkey51, _l_extendedprice55, _l_discount56};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_2591_input.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _p_partkey284_k = tbl_SerializeFromObject_TD_2591_input.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1915_key_leftMajor{_p_partkey284_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_partkey51 = (it->second)._l_partkey51;
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _p_partkey284 = tbl_SerializeFromObject_TD_2591_input.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288_n = tbl_SerializeFromObject_TD_2591_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _p_type288 = std::string(_p_type288_n.data());
                tbl_JOIN_INNER_TD_1915_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_1915_output.setInt32(r, 1, _l_discount56);
                tbl_JOIN_INNER_TD_1915_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _p_type288_n);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_1915_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1915_key_rightMajor, SW_JOIN_INNER_TD_1915_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_2591_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _p_partkey284_k = tbl_SerializeFromObject_TD_2591_input.getInt32(i, 0);
            SW_JOIN_INNER_TD_1915_key_rightMajor keyA{_p_partkey284_k};
            int32_t _p_partkey284 = tbl_SerializeFromObject_TD_2591_input.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288_n = tbl_SerializeFromObject_TD_2591_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _p_type288 = std::string(_p_type288_n.data());
            SW_JOIN_INNER_TD_1915_payload_rightMajor payloadA{_p_partkey284, _p_type288};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_244_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _l_partkey51_k = tbl_Filter_TD_244_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1915_key_rightMajor{_l_partkey51_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                std::string _p_type288 = (it->second)._p_type288;
                std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288_n{};
                memcpy(_p_type288_n.data(), (_p_type288).data(), (_p_type288).length());
                int32_t _l_partkey51 = tbl_Filter_TD_244_output.getInt32(i, 0);
                int32_t _l_extendedprice55 = tbl_Filter_TD_244_output.getInt32(i, 1);
                int32_t _l_discount56 = tbl_Filter_TD_244_output.getInt32(i, 2);
                tbl_JOIN_INNER_TD_1915_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _p_type288_n);
                tbl_JOIN_INNER_TD_1915_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_1915_output.setInt32(r, 1, _l_discount56);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_1915_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_1915_output #Row: " << tbl_JOIN_INNER_TD_1915_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_0256(Table &tbl_JOIN_INNER_TD_1915_output, Table &tbl_Aggregate_TD_0256_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer((cast((100 * sum(CASE WHEN StartsWith(p_type#288, PROMO) THEN (l_extendedprice#55 * (100 - l_discount#56)) ELSE 0 END)) as double) / cast(sum((l_extendedprice#55 * (100 - l_discount#56))) as double)) AS promo_revenue#1671)
    // Input: ListBuffer(l_extendedprice#55, l_discount#56, p_type#288)
    // Output: ListBuffer(promo_revenue#1671)
    int64_t sum_0 = 0;
    int64_t sum_1 = 0;
    int nrow1 = tbl_JOIN_INNER_TD_1915_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_1915_output.getInt32(i, 0);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_1915_output.getInt32(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_JOIN_INNER_TD_1915_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        int64_t _promo_revenue1671_sum_0 = (std::string(_p_type288.data()).find("PROMO")==0) ? (_l_extendedprice55 * (100 - _l_discount56)) : 0;
        int64_t _promo_revenue1671_sum_1 = (_l_extendedprice55 * (100 - _l_discount56));
        sum_0 += _promo_revenue1671_sum_0;
        sum_1 += _promo_revenue1671_sum_1;
    }
    int r = 0;
    int64_t _promo_revenue1671 = ((100 * sum_0) / sum_1);
    tbl_Aggregate_TD_0256_output.setInt64(r++, 0, _promo_revenue1671);
    tbl_Aggregate_TD_0256_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_0256_output #Row: " << tbl_Aggregate_TD_0256_output.getNumRow() << std::endl;
}

