#include <regex> 
#include <stdint.h> 

void SW_Project_TD_8778(Table &tbl_SerializeFromObject_TD_9246_input, Table &tbl_Project_TD_8778_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(cast(l_orderkey#1284L as int) AS l_orderkey#32, cast(CheckOverflow((promote_precision(l_quantity#1288) * 100.00), DecimalType(16,2), true) as int) AS l_quantity#100)
    // Input: ListBuffer(l_orderkey#1284L, l_quantity#1288)
    // Output: ListBuffer(l_orderkey#32, l_quantity#100)
    int nrow1 = tbl_SerializeFromObject_TD_9246_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_orderkey1284L = tbl_SerializeFromObject_TD_9246_input.getInt32(i, 0);
        int32_t _l_quantity1288 = tbl_SerializeFromObject_TD_9246_input.getInt32(i, 1);
        int32_t _l_orderkey32 = _l_orderkey1284L;
        tbl_Project_TD_8778_output.setInt32(i, 0, _l_orderkey32);
        int32_t _l_quantity100 = (_l_quantity1288 * 100.00);
        tbl_Project_TD_8778_output.setInt32(i, 1, _l_quantity100);
    }
    tbl_Project_TD_8778_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_8778_output #Row: " << tbl_Project_TD_8778_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_7384_consolidate(Table &tbl_Aggregate_TD_7384_output_preprocess, Table &tbl_Aggregate_TD_7384_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_7384_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _l_orderkey32 = tbl_Aggregate_TD_7384_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_7384_output.setInt32(r, 0, _l_orderkey32);
        int64_t _suml_quantity1001283L = tbl_Aggregate_TD_7384_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_7384_output.setInt64(r, 1, _suml_quantity1001283L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_7384_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_7384_output #Row: " << tbl_Aggregate_TD_7384_output.getNumRow() << std::endl;
}

void SW_Filter_TD_623(Table &tbl_Aggregate_TD_7384_output, Table &tbl_Filter_TD_623_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(sum(l_quantity#100)#1283L) AND (sum(l_quantity#100)#1283L > 312)))
    // Input: ListBuffer(l_orderkey#32, sum(l_quantity#100)#1283L)
    // Output: ListBuffer(l_orderkey#32)
    int r = 0;
    int nrow1 = tbl_Aggregate_TD_7384_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int64_t _suml_quantity1001283L = tbl_Aggregate_TD_7384_output.getInt64(i, 1);
        if ((1) && (_suml_quantity1001283L > 312)) {
            int32_t _l_orderkey32_t = tbl_Aggregate_TD_7384_output.getInt32(i, 0);
            tbl_Filter_TD_623_output.setInt32(r, 0, _l_orderkey32_t);
            r++;
        }
    }
    tbl_Filter_TD_623_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_623_output #Row: " << tbl_Filter_TD_623_output.getNumRow() << std::endl;
}

struct SW_JOIN_LEFTSEMI_TD_563_key_leftMajor {
    int64_t _o_orderkey324L;
    bool operator==(const SW_JOIN_LEFTSEMI_TD_563_key_leftMajor& other) const {
        return ((_o_orderkey324L == other._o_orderkey324L));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_LEFTSEMI_TD_563_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_LEFTSEMI_TD_563_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int64_t>()(k._o_orderkey324L));
    }
};
}
struct SW_JOIN_LEFTSEMI_TD_563_payload_leftMajor {
    int64_t _o_orderkey324L;
    int64_t _o_custkey325L;
    int32_t _o_totalprice327;
    // Unsupported join key type
};
struct SW_JOIN_LEFTSEMI_TD_563_key_rightMajor {
    int32_t _l_orderkey32;
    bool operator==(const SW_JOIN_LEFTSEMI_TD_563_key_rightMajor& other) const {
        return ((_l_orderkey32 == other._l_orderkey32));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_LEFTSEMI_TD_563_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_LEFTSEMI_TD_563_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._l_orderkey32));
    }
};
}
struct SW_JOIN_LEFTSEMI_TD_563_payload_rightMajor {
    int32_t _l_orderkey32;
};
void SW_JOIN_LEFTSEMI_TD_563(Table &tbl_SerializeFromObject_TD_7683_input, Table &tbl_Filter_TD_623_output, Table &tbl_JOIN_LEFTSEMI_TD_563_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_LEFTSEMI
    // Operation: ListBuffer((cast(o_orderkey#324L as int) = l_orderkey#32))
    // Left Table: ListBuffer(o_orderkey#324L, o_custkey#325L, o_totalprice#327, o_orderdate#332)
    // Right Table: ListBuffer(l_orderkey#32)
    // Output Table: ListBuffer(o_orderkey#324L, o_custkey#325L, o_totalprice#327, o_orderdate#332)
    int left_nrow = tbl_SerializeFromObject_TD_7683_input.getNumRow();
    int right_nrow = tbl_Filter_TD_623_output.getNumRow();
        std::unordered_map<SW_JOIN_LEFTSEMI_TD_563_key_rightMajor, SW_JOIN_LEFTSEMI_TD_563_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_623_output.getNumRow();
        int nrow2 = tbl_SerializeFromObject_TD_7683_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _l_orderkey32_k = tbl_Filter_TD_623_output.getInt32(i, 0);
            SW_JOIN_LEFTSEMI_TD_563_key_rightMajor keyA{_l_orderkey32_k};
            int32_t _l_orderkey32 = tbl_Filter_TD_623_output.getInt32(i, 0);
            SW_JOIN_LEFTSEMI_TD_563_payload_rightMajor payloadA{_l_orderkey32};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        for (int i = 0; i < nrow2; i++) {
            int64_t _o_orderkey324L_k = tbl_SerializeFromObject_TD_7683_input.getInt64(i, 0);
            auto it = ht1.find(SW_JOIN_LEFTSEMI_TD_563_key_rightMajor{_o_orderkey324L_k});
            if (it != ht1.end()) {
                int64_t _o_orderkey324L = tbl_SerializeFromObject_TD_7683_input.getInt64(i, 0);
                int64_t _o_custkey325L = tbl_SerializeFromObject_TD_7683_input.getInt64(i, 1);
                int32_t _o_totalprice327 = tbl_SerializeFromObject_TD_7683_input.getInt32(i, 2);
                // Unsupported join key type
                if (_o_orderkey324L == _l_orderkey32) {
                    tbl_JOIN_LEFTSEMI_TD_563_output.setInt64(r, 0, _o_orderkey324L);
                    tbl_JOIN_LEFTSEMI_TD_563_output.setInt64(r, 1, _o_custkey325L);
                    tbl_JOIN_LEFTSEMI_TD_563_output.setInt32(r, 2, _o_totalprice327);
                    // Unsupported join key type
                    r++;
                }
            }
        }
        tbl_JOIN_LEFTSEMI_TD_563_output.setNumRow(r);
    std::cout << "tbl_JOIN_LEFTSEMI_TD_563_output #Row: " << tbl_JOIN_LEFTSEMI_TD_563_output.getNumRow() << std::endl;
}

struct SW_JOIN_LEFTSEMI_TD_4174_key_leftMajor {
    int64_t _l_orderkey0L;
    bool operator==(const SW_JOIN_LEFTSEMI_TD_4174_key_leftMajor& other) const {
        return ((_l_orderkey0L == other._l_orderkey0L));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_LEFTSEMI_TD_4174_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_LEFTSEMI_TD_4174_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int64_t>()(k._l_orderkey0L));
    }
};
}
struct SW_JOIN_LEFTSEMI_TD_4174_payload_leftMajor {
    int64_t _l_orderkey0L;
    int32_t _l_quantity4;
};
struct SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor {
    int32_t _l_orderkey32;
    bool operator==(const SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor& other) const {
        return ((_l_orderkey32 == other._l_orderkey32));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._l_orderkey32));
    }
};
}
struct SW_JOIN_LEFTSEMI_TD_4174_payload_rightMajor {
    int32_t _l_orderkey32;
};
void SW_JOIN_LEFTSEMI_TD_4174(Table &tbl_SerializeFromObject_TD_6669_input, Table &tbl_Filter_TD_623_output, Table &tbl_JOIN_LEFTSEMI_TD_4174_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_LEFTSEMI
    // Operation: ListBuffer((cast(l_orderkey#0L as int) = l_orderkey#32))
    // Left Table: ListBuffer(l_orderkey#0L, l_quantity#4)
    // Right Table: ListBuffer(l_orderkey#32)
    // Output Table: ListBuffer(l_orderkey#0L, l_quantity#4)
    int left_nrow = tbl_SerializeFromObject_TD_6669_input.getNumRow();
    int right_nrow = tbl_Filter_TD_623_output.getNumRow();
        std::unordered_map<SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor, SW_JOIN_LEFTSEMI_TD_4174_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_623_output.getNumRow();
        int nrow2 = tbl_SerializeFromObject_TD_6669_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _l_orderkey32_k = tbl_Filter_TD_623_output.getInt32(i, 0);
            SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor keyA{_l_orderkey32_k};
            int32_t _l_orderkey32 = tbl_Filter_TD_623_output.getInt32(i, 0);
            SW_JOIN_LEFTSEMI_TD_4174_payload_rightMajor payloadA{_l_orderkey32};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        for (int i = 0; i < nrow2; i++) {
            int64_t _l_orderkey0L_k = tbl_SerializeFromObject_TD_6669_input.getInt64(i, 0);
            auto it = ht1.find(SW_JOIN_LEFTSEMI_TD_4174_key_rightMajor{_l_orderkey0L_k});
            if (it != ht1.end()) {
                int64_t _l_orderkey0L = tbl_SerializeFromObject_TD_6669_input.getInt64(i, 0);
                int32_t _l_quantity4 = tbl_SerializeFromObject_TD_6669_input.getInt32(i, 1);
                if (_l_orderkey0L == _l_orderkey32) {
                    tbl_JOIN_LEFTSEMI_TD_4174_output.setInt64(r, 0, _l_orderkey0L);
                    tbl_JOIN_LEFTSEMI_TD_4174_output.setInt32(r, 1, _l_quantity4);
                    r++;
                }
            }
        }
        tbl_JOIN_LEFTSEMI_TD_4174_output.setNumRow(r);
    std::cout << "tbl_JOIN_LEFTSEMI_TD_4174_output #Row: " << tbl_JOIN_LEFTSEMI_TD_4174_output.getNumRow() << std::endl;
}

void SW_Project_TD_4576(Table &tbl_JOIN_LEFTSEMI_TD_563_output, Table &tbl_Project_TD_4576_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(cast(o_orderkey#324L as int) AS o_orderkey#342, cast(o_custkey#325L as int) AS o_custkey#352, cast(CheckOverflow((promote_precision(o_totalprice#327) * 100.00), DecimalType(16,2), true) as int) AS o_totalprice#372, cast(regexp_replace(cast(o_orderdate#332 as string), -, , 1) as int) AS o_orderdate#382)
    // Input: ListBuffer(o_orderkey#324L, o_custkey#325L, o_totalprice#327, o_orderdate#332)
    // Output: ListBuffer(o_orderkey#342, o_custkey#352, o_totalprice#372, o_orderdate#382)
    int nrow1 = tbl_JOIN_LEFTSEMI_TD_563_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderkey324L = tbl_JOIN_LEFTSEMI_TD_563_output.getInt32(i, 0);
        int32_t _o_custkey325L = tbl_JOIN_LEFTSEMI_TD_563_output.getInt32(i, 1);
        int32_t _o_totalprice327 = tbl_JOIN_LEFTSEMI_TD_563_output.getInt32(i, 2);
        int32_t _o_orderdate332 = tbl_JOIN_LEFTSEMI_TD_563_output.getInt32(i, 3);
        int32_t _o_orderkey342 = _o_orderkey324L;
        tbl_Project_TD_4576_output.setInt32(i, 0, _o_orderkey342);
        int32_t _o_custkey352 = _o_custkey325L;
        tbl_Project_TD_4576_output.setInt32(i, 1, _o_custkey352);
        int32_t _o_totalprice372 = (_o_totalprice327 * 100.00);
        tbl_Project_TD_4576_output.setInt32(i, 2, _o_totalprice372);
        int32_t _o_orderdate382 = _o_orderdate332;
        tbl_Project_TD_4576_output.setInt32(i, 3, _o_orderdate382);
    }
    tbl_Project_TD_4576_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_4576_output #Row: " << tbl_Project_TD_4576_output.getNumRow() << std::endl;
}

void SW_Project_TD_4227(Table &tbl_SerializeFromObject_TD_6603_input_stringRowIDSubstitute, Table &tbl_Project_TD_4227_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(cast(c_custkey#253L as int) AS c_custkey#269)
    // Input: ListBuffer(c_custkey#253L, c_name#254)
    // Output: ListBuffer(c_custkey#269, c_name#254)
    int nrow1 = tbl_SerializeFromObject_TD_6603_input_stringRowIDSubstitute.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_custkey253L = tbl_SerializeFromObject_TD_6603_input_stringRowIDSubstitute.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name254 = tbl_SerializeFromObject_TD_6603_input_stringRowIDSubstitute.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        int32_t _c_custkey269 = _c_custkey253L;
        tbl_Project_TD_4227_output.setInt32(i, 0, _c_custkey269);
        tbl_Project_TD_4227_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1, _c_name254);
    }
    tbl_Project_TD_4227_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_4227_output #Row: " << tbl_Project_TD_4227_output.getNumRow() << std::endl;
}

void SW_Project_TD_3733(Table &tbl_JOIN_LEFTSEMI_TD_4174_output, Table &tbl_Project_TD_3733_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(cast(l_orderkey#0L as int) AS l_orderkey#32, cast(CheckOverflow((promote_precision(l_quantity#4) * 100.00), DecimalType(16,2), true) as int) AS l_quantity#100)
    // Input: ListBuffer(l_orderkey#0L, l_quantity#4)
    // Output: ListBuffer(l_orderkey#32, l_quantity#100)
    int nrow1 = tbl_JOIN_LEFTSEMI_TD_4174_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_orderkey0L = tbl_JOIN_LEFTSEMI_TD_4174_output.getInt32(i, 0);
        int32_t _l_quantity4 = tbl_JOIN_LEFTSEMI_TD_4174_output.getInt32(i, 1);
        int32_t _l_orderkey32 = _l_orderkey0L;
        tbl_Project_TD_3733_output.setInt32(i, 0, _l_orderkey32);
        int32_t _l_quantity100 = (_l_quantity4 * 100.00);
        tbl_Project_TD_3733_output.setInt32(i, 1, _l_quantity100);
    }
    tbl_Project_TD_3733_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_3733_output #Row: " << tbl_Project_TD_3733_output.getNumRow() << std::endl;
}



struct SW_Aggregate_TD_1591_key {
    std::string _c_name254;
    int32_t _c_custkey269;
    int32_t _o_orderkey342;
    int32_t _o_orderdate382;
    int32_t _o_totalprice372;
    bool operator==(const SW_Aggregate_TD_1591_key& other) const { return (_c_name254 == other._c_name254) && (_c_custkey269 == other._c_custkey269) && (_o_orderkey342 == other._o_orderkey342) && (_o_orderdate382 == other._o_orderdate382) && (_o_totalprice372 == other._o_totalprice372); }
};
namespace std {
template <>
struct hash<SW_Aggregate_TD_1591_key> {
    std::size_t operator() (const SW_Aggregate_TD_1591_key& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<string>()(k._c_name254)) + (hash<int32_t>()(k._c_custkey269)) + (hash<int32_t>()(k._o_orderkey342)) + (hash<int32_t>()(k._o_orderdate382)) + (hash<int32_t>()(k._o_totalprice372));
    }
};
}
struct SW_Aggregate_TD_1591_payload {
    int64_t _suml_quantity1301L_sum_0;
};
void SW_Aggregate_TD_1591(Table &tbl_JOIN_INNER_TD_2239_output, Table &tbl_SerializeFromObject_TD_6603_input, Table &tbl_Aggregate_TD_1591_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Aggregate
    // Operation: ListBuffer(c_name#254, c_custkey#269, o_orderkey#342, o_orderdate#382, o_totalprice#372, sum(l_quantity#100) AS sum(l_quantity)#1301L)
    // Input: ListBuffer(c_custkey#269, c_name#254, o_orderkey#342, o_totalprice#372, o_orderdate#382, l_quantity#100)
    // Output: ListBuffer(c_name#254, c_custkey#269, o_orderkey#342, o_orderdate#382, o_totalprice#372, sum(l_quantity)#1301L)
    std::unordered_map<SW_Aggregate_TD_1591_key, SW_Aggregate_TD_1591_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2239_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_custkey269 = tbl_JOIN_INNER_TD_2239_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name254 = tbl_SerializeFromObject_TD_6603_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2239_output.getInt32(i, 1), 1);
        int32_t _o_orderkey342 = tbl_JOIN_INNER_TD_2239_output.getInt32(i, 2);
        int32_t _o_totalprice372 = tbl_JOIN_INNER_TD_2239_output.getInt32(i, 3);
        int32_t _o_orderdate382 = tbl_JOIN_INNER_TD_2239_output.getInt32(i, 4);
        int32_t _l_quantity100 = tbl_JOIN_INNER_TD_2239_output.getInt32(i, 5);
        SW_Aggregate_TD_1591_key k{std::string(_c_name254.data()), _c_custkey269, _o_orderkey342, _o_orderdate382, _o_totalprice372};
        int64_t _suml_quantity1301L_sum_0 = _l_quantity100;
        SW_Aggregate_TD_1591_payload p{_suml_quantity1301L_sum_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._suml_quantity1301L_sum_0 + _suml_quantity1301L_sum_0;
            p._suml_quantity1301L_sum_0 = sum_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name254{};
        memcpy(_c_name254.data(), ((it.first)._c_name254).data(), ((it.first)._c_name254).length());
        tbl_Aggregate_TD_1591_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _c_name254);
        tbl_Aggregate_TD_1591_output.setInt32(r, 1, (it.first)._c_custkey269);
        tbl_Aggregate_TD_1591_output.setInt32(r, 2, (it.first)._o_orderkey342);
        tbl_Aggregate_TD_1591_output.setInt32(r, 3, (it.first)._o_orderdate382);
        tbl_Aggregate_TD_1591_output.setInt32(r, 4, (it.first)._o_totalprice372);
        int64_t _suml_quantity1301L = (it.second)._suml_quantity1301L_sum_0;
        tbl_Aggregate_TD_1591_output.setInt64(r, 5, _suml_quantity1301L);
        ++r;
    }
    tbl_Aggregate_TD_1591_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1591_output #Row: " << tbl_Aggregate_TD_1591_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0338(Table &tbl_Aggregate_TD_1591_output, Table &tbl_Sort_TD_0338_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(o_totalprice#372 DESC NULLS LAST, o_orderdate#382 ASC NULLS FIRST)
    // Input: ListBuffer(c_name#254, c_custkey#269, o_orderkey#342, o_orderdate#382, o_totalprice#372, sum(l_quantity)#1301L)
    // Output: ListBuffer(c_name#254, c_custkey#269, o_orderkey#342, o_orderdate#382, o_totalprice#372, sum(l_quantity)#1301L)
    struct SW_Sort_TD_0338Row {
        std::string _c_name254;
        int32_t _c_custkey269;
        int32_t _o_orderkey342;
        int32_t _o_orderdate382;
        int32_t _o_totalprice372;
        int64_t _suml_quantity1301L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0338Row& a, const SW_Sort_TD_0338Row& b) const { return 
 (a._o_totalprice372 > b._o_totalprice372) || 
 ((a._o_totalprice372 == b._o_totalprice372) && (a._o_orderdate382 < b._o_orderdate382)); 
}
    }SW_Sort_TD_0338_order; 

    int nrow1 = tbl_Aggregate_TD_1591_output.getNumRow();
    std::vector<SW_Sort_TD_0338Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name254 = tbl_Aggregate_TD_1591_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int32_t _c_custkey269 = tbl_Aggregate_TD_1591_output.getInt32(i, 1);
        int32_t _o_orderkey342 = tbl_Aggregate_TD_1591_output.getInt32(i, 2);
        int32_t _o_orderdate382 = tbl_Aggregate_TD_1591_output.getInt32(i, 3);
        int32_t _o_totalprice372 = tbl_Aggregate_TD_1591_output.getInt32(i, 4);
        int64_t _suml_quantity1301L = tbl_Aggregate_TD_1591_output.getInt64(i, 5);
        SW_Sort_TD_0338Row t = {std::string(_c_name254.data()),_c_custkey269,_o_orderkey342,_o_orderdate382,_o_totalprice372,_suml_quantity1301L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0338_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name254{};
        memcpy(_c_name254.data(), (it._c_name254).data(), (it._c_name254).length());
        tbl_Sort_TD_0338_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _c_name254);
        tbl_Sort_TD_0338_output.setInt32(r, 1, it._c_custkey269);
        tbl_Sort_TD_0338_output.setInt32(r, 2, it._o_orderkey342);
        tbl_Sort_TD_0338_output.setInt32(r, 3, it._o_orderdate382);
        tbl_Sort_TD_0338_output.setInt32(r, 4, it._o_totalprice372);
        tbl_Sort_TD_0338_output.setInt64(r, 5, it._suml_quantity1301L);
        if (r < 10) {
            std::cout << (it._c_name254).data() << " " << it._c_custkey269 << " " << it._o_orderkey342 << " " << it._o_orderdate382 << " " << it._o_totalprice372 << " " << it._suml_quantity1301L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0338_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0338_output #Row: " << tbl_Sort_TD_0338_output.getNumRow() << std::endl;
}

