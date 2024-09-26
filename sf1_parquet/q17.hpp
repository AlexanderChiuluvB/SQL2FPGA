#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_3458(Table &tbl_SerializeFromObject_TD_4449_input, Table &tbl_Filter_TD_3458_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((isnotnull(p_brand#287) AND isnotnull(p_container#290)) AND ((p_brand#287 = Brand#21) AND (p_container#290 = WRAP BAG))))
    // Input: ListBuffer(p_partkey#284, p_brand#287, p_container#290)
    // Output: ListBuffer(p_partkey#284)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4449_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287 = tbl_SerializeFromObject_TD_4449_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_container290 = tbl_SerializeFromObject_TD_4449_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        if (((1) && (1)) && ((std::string(_p_brand287.data()) == "Brand#21") && (std::string(_p_container290.data()) == "WRAP BAG"))) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_4449_input.getInt32(i, 0);
            tbl_Filter_TD_3458_output.setInt32(r, 0, _p_partkey284_t);
            r++;
        }
    }
    tbl_Filter_TD_3458_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3458_output #Row: " << tbl_Filter_TD_3458_output.getNumRow() << std::endl;
}

typedef int32_t SW_Aggregate_TD_3595_key;
struct SW_Aggregate_TD_3595_payload {
    int64_t _avgl_quantity1880_avg_0;
    int32_t _l_partkey511941;
};
void SW_Aggregate_TD_3595(Table &tbl_SerializeFromObject_TD_4718_input, Table &tbl_Aggregate_TD_3595_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(l_partkey#51, (0.2 * avg(l_quantity#54)) AS (0.2 * avg(l_quantity))#1880, l_partkey#51 AS l_partkey#51#1941)
    // Input: ListBuffer(l_partkey#51, l_quantity#54)
    // Output: ListBuffer((0.2 * avg(l_quantity))#1880, l_partkey#51#1941)
    std::unordered_map<SW_Aggregate_TD_3595_key, SW_Aggregate_TD_3595_payload> ht1;
    int nrow1 = tbl_SerializeFromObject_TD_4718_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_partkey51 = tbl_SerializeFromObject_TD_4718_input.getInt32(i, 0);
        int32_t _l_quantity54 = tbl_SerializeFromObject_TD_4718_input.getInt32(i, 1);
        SW_Aggregate_TD_3595_key k = _l_partkey51;
        int64_t _avgl_quantity1880_avg_0 = _l_quantity54;
        int32_t _l_partkey511941 = _l_partkey51;
        SW_Aggregate_TD_3595_payload p{_avgl_quantity1880_avg_0, _l_partkey511941};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t avg_0 = ((it->second)._avgl_quantity1880_avg_0 + _avgl_quantity1880_avg_0);
            p._avgl_quantity1880_avg_0 = avg_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        // _l_partkey51 not required in the output table
        int64_t _avgl_quantity1880 = (0.2 * (it.second)._avgl_quantity1880_avg_0 / nrow1);
        tbl_Aggregate_TD_3595_output.setInt64(r, 0, _avgl_quantity1880);
        tbl_Aggregate_TD_3595_output.setInt32(r, 1, (it.second)._l_partkey511941);
        ++r;
    }
    tbl_Aggregate_TD_3595_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_3595_output #Row: " << tbl_Aggregate_TD_3595_output.getNumRow() << std::endl;
}


struct SW_JOIN_INNER_TD_165_key_leftMajor {
    int32_t _p_partkey284;
    bool operator==(const SW_JOIN_INNER_TD_165_key_leftMajor& other) const {
        return ((_p_partkey284 == other._p_partkey284));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_165_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_165_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._p_partkey284));
    }
};
}
struct SW_JOIN_INNER_TD_165_payload_leftMajor {
    int32_t _l_quantity54;
    int32_t _l_extendedprice55;
    int32_t _p_partkey284;
};
struct SW_JOIN_INNER_TD_165_key_rightMajor {
    int32_t _l_partkey511941;
    bool operator==(const SW_JOIN_INNER_TD_165_key_rightMajor& other) const {
        return ((_l_partkey511941 == other._l_partkey511941));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_165_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_165_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._l_partkey511941));
    }
};
}
struct SW_JOIN_INNER_TD_165_payload_rightMajor {
    int64_t _avgl_quantity1880;
    int32_t _l_partkey511941;
};
void SW_JOIN_INNER_TD_165(Table &tbl_JOIN_INNER_TD_248_output, Table &tbl_Aggregate_TD_3595_output, Table &tbl_JOIN_INNER_TD_165_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer(((cast(l_quantity#54 as double) < (0.2 * avg(l_quantity))#1880) AND (l_partkey#51#1941 = p_partkey#284)))
    // Left Table: ListBuffer(l_quantity#54, l_extendedprice#55, p_partkey#284)
    // Right Table: ListBuffer((0.2 * avg(l_quantity))#1880, l_partkey#51#1941)
    // Output Table: ListBuffer(l_extendedprice#55)
    int left_nrow = tbl_JOIN_INNER_TD_248_output.getNumRow();
    int right_nrow = tbl_Aggregate_TD_3595_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_165_key_leftMajor, SW_JOIN_INNER_TD_165_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_248_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _p_partkey284_k = tbl_JOIN_INNER_TD_248_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_165_key_leftMajor keyA{_p_partkey284_k};
            int32_t _l_quantity54 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 0);
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 1);
            int32_t _p_partkey284 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_165_payload_leftMajor payloadA{_l_quantity54, _l_extendedprice55, _p_partkey284};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Aggregate_TD_3595_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _l_partkey511941_k = tbl_Aggregate_TD_3595_output.getInt32(i, 1);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_165_key_leftMajor{_l_partkey511941_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_quantity54 = (it->second)._l_quantity54;
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                int64_t _avgl_quantity1880 = tbl_Aggregate_TD_3595_output.getInt64(i, 0);
                int32_t _l_partkey511941 = tbl_Aggregate_TD_3595_output.getInt32(i, 1);
                if (_l_quantity54 < _avgl_quantity1880) {
                    tbl_JOIN_INNER_TD_165_output.setInt32(r, 0, _l_extendedprice55);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_165_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_165_key_rightMajor, SW_JOIN_INNER_TD_165_payload_rightMajor> ht1;
        int nrow1 = tbl_Aggregate_TD_3595_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _l_partkey511941_k = tbl_Aggregate_TD_3595_output.getInt32(i, 1);
            SW_JOIN_INNER_TD_165_key_rightMajor keyA{_l_partkey511941_k};
            int64_t _avgl_quantity1880 = tbl_Aggregate_TD_3595_output.getInt64(i, 0);
            int32_t _l_partkey511941 = tbl_Aggregate_TD_3595_output.getInt32(i, 1);
            SW_JOIN_INNER_TD_165_payload_rightMajor payloadA{_avgl_quantity1880, _l_partkey511941};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_248_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _p_partkey284_k = tbl_JOIN_INNER_TD_248_output.getInt32(i, 2);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_165_key_rightMajor{_p_partkey284_k});
            auto it = its.first;
            while (it != its.second) {
                int64_t _avgl_quantity1880 = (it->second)._avgl_quantity1880;
                int32_t _l_partkey511941 = (it->second)._l_partkey511941;
                int32_t _l_quantity54 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 0);
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 1);
                int32_t _p_partkey284 = tbl_JOIN_INNER_TD_248_output.getInt32(i, 2);
                if (_l_quantity54 < _avgl_quantity1880) {
                    tbl_JOIN_INNER_TD_165_output.setInt32(r, 0, _l_extendedprice55);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_165_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_165_output #Row: " << tbl_JOIN_INNER_TD_165_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_02(Table &tbl_JOIN_INNER_TD_165_output, Table &tbl_Aggregate_TD_02_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(CheckOverflow((promote_precision(cast(cast(sum(l_extendedprice#55) as decimal(20,0)) as decimal(21,1))) / 7.0), DecimalType(27,6), true) AS avg_yearly#1877)
    // Input: ListBuffer(l_extendedprice#55)
    // Output: ListBuffer(avg_yearly#1877)
    int64_t sum_0 = 0;
    int nrow1 = tbl_JOIN_INNER_TD_165_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_165_output.getInt32(i, 0);
        int64_t _avg_yearly1877_sum_0 = _l_extendedprice55;
        sum_0 += _avg_yearly1877_sum_0;
    }
    int r = 0;
    int64_t _avg_yearly1877 = (sum_0 / 7.0);
    tbl_Aggregate_TD_02_output.setInt64(r++, 0, _avg_yearly1877);
    tbl_Aggregate_TD_02_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_02_output #Row: " << tbl_Aggregate_TD_02_output.getNumRow() << std::endl;
}

