#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_8765(Table &tbl_SerializeFromObject_TD_9451_input, Table &tbl_Filter_TD_8765_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((l_shipdate#60 >= 19950101) AND (l_shipdate#60 <= 19961231)))
    // Input: ListBuffer(l_orderkey#50, l_suppkey#52, l_extendedprice#55, l_discount#56, l_shipdate#60)
    // Output: ListBuffer(l_orderkey#50, l_suppkey#52, l_extendedprice#55, l_discount#56, l_shipdate#60)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_9451_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 4);
        if ((_l_shipdate60 >= 19950101) && (_l_shipdate60 <= 19961231)) {
            int32_t _l_orderkey50_t = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 0);
            tbl_Filter_TD_8765_output.setInt32(r, 0, _l_orderkey50_t);
            int32_t _l_suppkey52_t = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 1);
            tbl_Filter_TD_8765_output.setInt32(r, 1, _l_suppkey52_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 2);
            tbl_Filter_TD_8765_output.setInt32(r, 2, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 3);
            tbl_Filter_TD_8765_output.setInt32(r, 3, _l_discount56_t);
            int32_t _l_shipdate60_t = tbl_SerializeFromObject_TD_9451_input.getInt32(i, 4);
            tbl_Filter_TD_8765_output.setInt32(r, 4, _l_shipdate60_t);
            r++;
        }
    }
    tbl_Filter_TD_8765_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_8765_output #Row: " << tbl_Filter_TD_8765_output.getNumRow() << std::endl;
}

void SW_Filter_TD_5228(Table &tbl_SerializeFromObject_TD_6439_input, Table &tbl_Filter_TD_5228_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((n_name#165 = FRANCE) OR (n_name#165 = IRAQ)))
    // Input: ListBuffer(n_nationkey#164, n_name#165)
    // Output: ListBuffer(n_nationkey#164, n_name#165)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_6439_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_6439_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((std::string(_n_name165.data()) == "FRANCE") || (std::string(_n_name165.data()) == "IRAQ")) {
            int32_t _n_nationkey164_t = tbl_SerializeFromObject_TD_6439_input.getInt32(i, 0);
            tbl_Filter_TD_5228_output.setInt32(r, 0, _n_nationkey164_t);
            tbl_Filter_TD_5228_output.setInt32(r, 1, i);
            r++;
        }
    }
    tbl_Filter_TD_5228_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_5228_output #Row: " << tbl_Filter_TD_5228_output.getNumRow() << std::endl;
}




void SW_Filter_TD_4739(Table &tbl_SerializeFromObject_TD_541_input, Table &tbl_Filter_TD_4739_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((n_name#1200 = IRAQ) OR (n_name#1200 = FRANCE)))
    // Input: ListBuffer(n_nationkey#1199, n_name#1200)
    // Output: ListBuffer(n_nationkey#1199, n_name#1200)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_541_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200 = tbl_SerializeFromObject_TD_541_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((std::string(_n_name1200.data()) == "IRAQ") || (std::string(_n_name1200.data()) == "FRANCE")) {
            int32_t _n_nationkey1199_t = tbl_SerializeFromObject_TD_541_input.getInt32(i, 0);
            tbl_Filter_TD_4739_output.setInt32(r, 0, _n_nationkey1199_t);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200_t = tbl_SerializeFromObject_TD_541_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            tbl_Filter_TD_4739_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _n_name1200_t);
            r++;
        }
    }
    tbl_Filter_TD_4739_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4739_output #Row: " << tbl_Filter_TD_4739_output.getNumRow() << std::endl;
}


struct SW_JOIN_INNER_TD_397_key_leftMajor {
    int32_t _c_nationkey128;
    bool operator==(const SW_JOIN_INNER_TD_397_key_leftMajor& other) const {
        return ((_c_nationkey128 == other._c_nationkey128));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_397_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_397_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._c_nationkey128));
    }
};
}
struct SW_JOIN_INNER_TD_397_payload_leftMajor {
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
    int32_t _l_shipdate60;
    int32_t _c_nationkey128;
    std::string _n_name165;
};
struct SW_JOIN_INNER_TD_397_key_rightMajor {
    int32_t _n_nationkey1199;
    bool operator==(const SW_JOIN_INNER_TD_397_key_rightMajor& other) const {
        return ((_n_nationkey1199 == other._n_nationkey1199));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_397_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_397_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_nationkey1199));
    }
};
}
struct SW_JOIN_INNER_TD_397_payload_rightMajor {
    int32_t _n_nationkey1199;
    std::string _n_name1200;
};
void SW_JOIN_INNER_TD_397(Table &tbl_JOIN_INNER_TD_4303_output, Table &tbl_Filter_TD_4739_output, Table &tbl_SerializeFromObject_TD_6439_input, Table &tbl_JOIN_INNER_TD_397_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer(((c_nationkey#128 = n_nationkey#1199) AND (((n_name#165 = FRANCE) AND (n_name#1200 = IRAQ)) OR ((n_name#165 = IRAQ) AND (n_name#1200 = FRANCE)))))
    // Left Table: ListBuffer(l_extendedprice#55, l_discount#56, l_shipdate#60, c_nationkey#128, n_name#165)
    // Right Table: ListBuffer(n_nationkey#1199, n_name#1200)
    // Output Table: ListBuffer(n_name#165, n_name#1200, l_shipdate#60, l_extendedprice#55, l_discount#56, c_nationkey#128)
    int left_nrow = tbl_JOIN_INNER_TD_4303_output.getNumRow();
    int right_nrow = tbl_Filter_TD_4739_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_397_key_leftMajor, SW_JOIN_INNER_TD_397_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_4303_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _c_nationkey128_k = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_397_key_leftMajor keyA{_c_nationkey128_k};
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 0);
            int32_t _l_discount56 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 1);
            int32_t _l_shipdate60 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 2);
            int32_t _c_nationkey128 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 3);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_6439_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_4303_output.getInt32(i, 4), 1);
            std::string _n_name165 = std::string(_n_name165_n.data());
            SW_JOIN_INNER_TD_397_payload_leftMajor payloadA{_l_extendedprice55, _l_discount56, _l_shipdate60, _c_nationkey128, _n_name165};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_4739_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_nationkey1199_k = tbl_Filter_TD_4739_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_397_key_leftMajor{_n_nationkey1199_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _l_shipdate60 = (it->second)._l_shipdate60;
                int32_t _c_nationkey128 = (it->second)._c_nationkey128;
                std::string _n_name165 = (it->second)._n_name165;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n{};
                memcpy(_n_name165_n.data(), (_n_name165).data(), (_n_name165).length());
                int32_t _n_nationkey1199 = tbl_Filter_TD_4739_output.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200_n = tbl_Filter_TD_4739_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _n_name1200 = std::string(_n_name1200_n.data());
                if (((_n_name165 == "FRANCE") && (_n_name1200 == "IRAQ")) || ((_n_name165 == "IRAQ") && (_n_name1200 == "FRANCE"))) {
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 3, _l_extendedprice55);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 4, _l_discount56);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 2, _l_shipdate60);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 5, _c_nationkey128);
                    tbl_JOIN_INNER_TD_397_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _n_name165_n);
                    tbl_JOIN_INNER_TD_397_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _n_name1200_n);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_397_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_397_key_rightMajor, SW_JOIN_INNER_TD_397_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_4739_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_nationkey1199_k = tbl_Filter_TD_4739_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_397_key_rightMajor keyA{_n_nationkey1199_k};
            int32_t _n_nationkey1199 = tbl_Filter_TD_4739_output.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200_n = tbl_Filter_TD_4739_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _n_name1200 = std::string(_n_name1200_n.data());
            SW_JOIN_INNER_TD_397_payload_rightMajor payloadA{_n_nationkey1199, _n_name1200};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_4303_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _c_nationkey128_k = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 3);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_397_key_rightMajor{_c_nationkey128_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _n_nationkey1199 = (it->second)._n_nationkey1199;
                std::string _n_name1200 = (it->second)._n_name1200;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200_n{};
                memcpy(_n_name1200_n.data(), (_n_name1200).data(), (_n_name1200).length());
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 0);
                int32_t _l_discount56 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 1);
                int32_t _l_shipdate60 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 2);
                int32_t _c_nationkey128 = tbl_JOIN_INNER_TD_4303_output.getInt32(i, 3);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_6439_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_4303_output.getInt32(i, 4), 1);
            std::string _n_name165 = std::string(_n_name165_n.data());
                if (((_n_name165 == "FRANCE") && (_n_name1200 == "IRAQ")) || ((_n_name165 == "IRAQ") && (_n_name1200 == "FRANCE"))) {
                    tbl_JOIN_INNER_TD_397_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _n_name1200_n);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 3, _l_extendedprice55);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 4, _l_discount56);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 2, _l_shipdate60);
                    tbl_JOIN_INNER_TD_397_output.setInt32(r, 5, _c_nationkey128);
                    tbl_JOIN_INNER_TD_397_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _n_name165_n);
                    r++;
                }
                it++;
            }
        }
        tbl_JOIN_INNER_TD_397_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_397_output #Row: " << tbl_JOIN_INNER_TD_397_output.getNumRow() << std::endl;
}

void SW_Project_TD_2726(Table &tbl_JOIN_INNER_TD_397_output, Table &tbl_Project_TD_2726_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(n_name#165 AS supp_nation#1190, n_name#1200 AS cust_nation#1191, cast((cast(l_shipdate#60 as double) / 10000.0) as int) AS l_year#1192, (l_extendedprice#55 * (100 - l_discount#56)) AS volume#1193)
    // Input: ListBuffer(n_name#165, n_name#1200, l_shipdate#60, l_extendedprice#55, l_discount#56, c_nationkey#128)
    // Output: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, volume#1193)
    int nrow1 = tbl_JOIN_INNER_TD_397_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_JOIN_INNER_TD_397_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1200 = tbl_JOIN_INNER_TD_397_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        int32_t _l_shipdate60 = tbl_JOIN_INNER_TD_397_output.getInt32(i, 2);
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_397_output.getInt32(i, 3);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_397_output.getInt32(i, 4);
        int32_t _c_nationkey128 = tbl_JOIN_INNER_TD_397_output.getInt32(i, 5);
        std::array<char, TPCH_READ_REGION_LEN + 1> _supp_nation1190 = _n_name165;
        tbl_Project_TD_2726_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0, _supp_nation1190);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cust_nation1191 = _n_name1200;
        tbl_Project_TD_2726_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1, _cust_nation1191);
        int32_t _l_year1192 = (_l_shipdate60 / 10000.0);
        tbl_Project_TD_2726_output.setInt32(i, 2, _l_year1192);
        int32_t _volume1193 = (_l_extendedprice55 * (100 - _l_discount56));
        tbl_Project_TD_2726_output.setInt32(i, 3, _volume1193);
    }
    tbl_Project_TD_2726_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_2726_output #Row: " << tbl_Project_TD_2726_output.getNumRow() << std::endl;
}

struct SW_Aggregate_TD_188_key {
    std::string _supp_nation1190;
    std::string _cust_nation1191;
    int32_t _l_year1192;
    bool operator==(const SW_Aggregate_TD_188_key& other) const { return (_supp_nation1190 == other._supp_nation1190) && (_cust_nation1191 == other._cust_nation1191) && (_l_year1192 == other._l_year1192); }
};
namespace std {
template <>
struct hash<SW_Aggregate_TD_188_key> {
    std::size_t operator() (const SW_Aggregate_TD_188_key& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<string>()(k._supp_nation1190)) + (hash<string>()(k._cust_nation1191)) + (hash<int32_t>()(k._l_year1192));
    }
};
}
struct SW_Aggregate_TD_188_payload {
    int64_t _revenue1194L_sum_0;
};
void SW_Aggregate_TD_188(Table &tbl_Project_TD_2726_output, Table &tbl_Aggregate_TD_188_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, sum(volume#1193) AS revenue#1194L)
    // Input: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, volume#1193)
    // Output: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, revenue#1194L)
    std::unordered_map<SW_Aggregate_TD_188_key, SW_Aggregate_TD_188_payload> ht1;
    int nrow1 = tbl_Project_TD_2726_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _supp_nation1190 = tbl_Project_TD_2726_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cust_nation1191 = tbl_Project_TD_2726_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        int32_t _l_year1192 = tbl_Project_TD_2726_output.getInt32(i, 2);
        int32_t _volume1193 = tbl_Project_TD_2726_output.getInt32(i, 3);
        SW_Aggregate_TD_188_key k{std::string(_supp_nation1190.data()), std::string(_cust_nation1191.data()), _l_year1192};
        int64_t _revenue1194L_sum_0 = _volume1193;
        SW_Aggregate_TD_188_payload p{_revenue1194L_sum_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._revenue1194L_sum_0 + _revenue1194L_sum_0;
            p._revenue1194L_sum_0 = sum_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _supp_nation1190{};
        memcpy(_supp_nation1190.data(), ((it.first)._supp_nation1190).data(), ((it.first)._supp_nation1190).length());
        tbl_Aggregate_TD_188_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _supp_nation1190);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cust_nation1191{};
        memcpy(_cust_nation1191.data(), ((it.first)._cust_nation1191).data(), ((it.first)._cust_nation1191).length());
        tbl_Aggregate_TD_188_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _cust_nation1191);
        tbl_Aggregate_TD_188_output.setInt32(r, 2, (it.first)._l_year1192);
        int64_t _revenue1194L = (it.second)._revenue1194L_sum_0;
        tbl_Aggregate_TD_188_output.setInt64(r, 3, _revenue1194L);
        ++r;
    }
    tbl_Aggregate_TD_188_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_188_output #Row: " << tbl_Aggregate_TD_188_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0417(Table &tbl_Aggregate_TD_188_output, Table &tbl_Sort_TD_0417_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(supp_nation#1190 ASC NULLS FIRST, cust_nation#1191 ASC NULLS FIRST, l_year#1192 ASC NULLS FIRST)
    // Input: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, revenue#1194L)
    // Output: ListBuffer(supp_nation#1190, cust_nation#1191, l_year#1192, revenue#1194L)
    struct SW_Sort_TD_0417Row {
        std::string _supp_nation1190;
        std::string _cust_nation1191;
        int32_t _l_year1192;
        int64_t _revenue1194L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0417Row& a, const SW_Sort_TD_0417Row& b) const { return 
 (a._supp_nation1190 < b._supp_nation1190) || 
 ((a._supp_nation1190 == b._supp_nation1190) && (a._cust_nation1191 < b._cust_nation1191)) || 
 ((a._supp_nation1190 == b._supp_nation1190) && (a._cust_nation1191 == b._cust_nation1191) && (a._l_year1192 < b._l_year1192)); 
}
    }SW_Sort_TD_0417_order; 

    int nrow1 = tbl_Aggregate_TD_188_output.getNumRow();
    std::vector<SW_Sort_TD_0417Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _supp_nation1190 = tbl_Aggregate_TD_188_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cust_nation1191 = tbl_Aggregate_TD_188_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 1);
        int32_t _l_year1192 = tbl_Aggregate_TD_188_output.getInt32(i, 2);
        int64_t _revenue1194L = tbl_Aggregate_TD_188_output.getInt64(i, 3);
        SW_Sort_TD_0417Row t = {std::string(_supp_nation1190.data()),std::string(_cust_nation1191.data()),_l_year1192,_revenue1194L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0417_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _supp_nation1190{};
        memcpy(_supp_nation1190.data(), (it._supp_nation1190).data(), (it._supp_nation1190).length());
        tbl_Sort_TD_0417_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _supp_nation1190);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cust_nation1191{};
        memcpy(_cust_nation1191.data(), (it._cust_nation1191).data(), (it._cust_nation1191).length());
        tbl_Sort_TD_0417_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _cust_nation1191);
        tbl_Sort_TD_0417_output.setInt32(r, 2, it._l_year1192);
        tbl_Sort_TD_0417_output.setInt64(r, 3, it._revenue1194L);
        if (r < 10) {
            std::cout << (it._supp_nation1190).data() << " " << (it._cust_nation1191).data() << " " << it._l_year1192 << " " << it._revenue1194L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0417_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0417_output #Row: " << tbl_Sort_TD_0417_output.getNumRow() << std::endl;
}

