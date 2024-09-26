#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_10125(Table &tbl_SerializeFromObject_TD_11681_input, Table &tbl_Filter_TD_10125_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(p_type#288) AND (p_type#288 = LARGE ANODIZED STEEL)))
    // Input: ListBuffer(p_partkey#284, p_type#288)
    // Output: ListBuffer(p_partkey#284)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_11681_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_SerializeFromObject_TD_11681_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_p_type288.data()) == "LARGE ANODIZED STEEL")) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_11681_input.getInt32(i, 0);
            tbl_Filter_TD_10125_output.setInt32(r, 0, _p_partkey284_t);
            r++;
        }
    }
    tbl_Filter_TD_10125_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_10125_output #Row: " << tbl_Filter_TD_10125_output.getNumRow() << std::endl;
}


void SW_Filter_TD_8847(Table &tbl_SerializeFromObject_TD_9848_input, Table &tbl_Filter_TD_8847_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((o_orderdate#231 >= 19950101) AND (o_orderdate#231 <= 19961231)))
    // Input: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231)
    // Output: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_9848_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderdate231 = tbl_SerializeFromObject_TD_9848_input.getInt32(i, 2);
        if ((_o_orderdate231 >= 19950101) && (_o_orderdate231 <= 19961231)) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_9848_input.getInt32(i, 0);
            tbl_Filter_TD_8847_output.setInt32(r, 0, _o_orderkey227_t);
            int32_t _o_custkey228_t = tbl_SerializeFromObject_TD_9848_input.getInt32(i, 1);
            tbl_Filter_TD_8847_output.setInt32(r, 1, _o_custkey228_t);
            int32_t _o_orderdate231_t = tbl_SerializeFromObject_TD_9848_input.getInt32(i, 2);
            tbl_Filter_TD_8847_output.setInt32(r, 2, _o_orderdate231_t);
            r++;
        }
    }
    tbl_Filter_TD_8847_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_8847_output #Row: " << tbl_Filter_TD_8847_output.getNumRow() << std::endl;
}




void SW_Filter_TD_4473(Table &tbl_SerializeFromObject_TD_5515_input, Table &tbl_Filter_TD_4473_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(r_name#189) AND (r_name#189 = MIDDLE EAST)))
    // Input: ListBuffer(r_regionkey#188, r_name#189)
    // Output: ListBuffer(r_regionkey#188)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5515_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _r_name189 = tbl_SerializeFromObject_TD_5515_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_r_name189.data()) == "MIDDLE EAST")) {
            int32_t _r_regionkey188_t = tbl_SerializeFromObject_TD_5515_input.getInt32(i, 0);
            tbl_Filter_TD_4473_output.setInt32(r, 0, _r_regionkey188_t);
            r++;
        }
    }
    tbl_Filter_TD_4473_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4473_output #Row: " << tbl_Filter_TD_4473_output.getNumRow() << std::endl;
}



struct SW_JOIN_INNER_TD_3840_key_leftMajor {
    int32_t _s_nationkey371;
    bool operator==(const SW_JOIN_INNER_TD_3840_key_leftMajor& other) const {
        return ((_s_nationkey371 == other._s_nationkey371));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3840_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3840_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._s_nationkey371));
    }
};
}
struct SW_JOIN_INNER_TD_3840_payload_leftMajor {
    int32_t _o_orderdate231;
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
    int32_t _s_nationkey371;
    int32_t _n_regionkey166;
};
struct SW_JOIN_INNER_TD_3840_key_rightMajor {
    int32_t _n_nationkey1270;
    bool operator==(const SW_JOIN_INNER_TD_3840_key_rightMajor& other) const {
        return ((_n_nationkey1270 == other._n_nationkey1270));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3840_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3840_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_nationkey1270));
    }
};
}
struct SW_JOIN_INNER_TD_3840_payload_rightMajor {
    int32_t _n_nationkey1270;
    std::string _n_name1271;
};
void SW_JOIN_INNER_TD_3840(Table &tbl_JOIN_INNER_TD_4702_output, Table &tbl_SerializeFromObject_TD_4509_input, Table &tbl_JOIN_INNER_TD_3840_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((s_nationkey#371 = n_nationkey#1270))
    // Left Table: ListBuffer(o_orderdate#231, l_extendedprice#55, l_discount#56, s_nationkey#371, n_regionkey#166)
    // Right Table: ListBuffer(n_nationkey#1270, n_name#1271)
    // Output Table: ListBuffer(o_orderdate#231, l_extendedprice#55, l_discount#56, n_name#1271)
    int left_nrow = tbl_JOIN_INNER_TD_4702_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_4509_input.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3840_key_leftMajor, SW_JOIN_INNER_TD_3840_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_4702_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_3840_key_leftMajor keyA{_s_nationkey371_k};
            int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 0);
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 1);
            int32_t _l_discount56 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 2);
            int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 3);
            int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 4);
            SW_JOIN_INNER_TD_3840_payload_leftMajor payloadA{_o_orderdate231, _l_extendedprice55, _l_discount56, _s_nationkey371, _n_regionkey166};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_4509_input.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_nationkey1270_k = tbl_SerializeFromObject_TD_4509_input.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3840_key_leftMajor{_n_nationkey1270_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _o_orderdate231 = (it->second)._o_orderdate231;
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _s_nationkey371 = (it->second)._s_nationkey371;
                int32_t _n_regionkey166 = (it->second)._n_regionkey166;
                int32_t _n_nationkey1270 = tbl_SerializeFromObject_TD_4509_input.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1271_n = tbl_SerializeFromObject_TD_4509_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _n_name1271 = std::string(_n_name1271_n.data());
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 0, _o_orderdate231);
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 1, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 2, _l_discount56);
                tbl_JOIN_INNER_TD_3840_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 3, _n_name1271_n);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3840_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3840_key_rightMajor, SW_JOIN_INNER_TD_3840_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_4509_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_nationkey1270_k = tbl_SerializeFromObject_TD_4509_input.getInt32(i, 0);
            SW_JOIN_INNER_TD_3840_key_rightMajor keyA{_n_nationkey1270_k};
            int32_t _n_nationkey1270 = tbl_SerializeFromObject_TD_4509_input.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1271_n = tbl_SerializeFromObject_TD_4509_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _n_name1271 = std::string(_n_name1271_n.data());
            SW_JOIN_INNER_TD_3840_payload_rightMajor payloadA{_n_nationkey1270, _n_name1271};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_4702_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 3);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3840_key_rightMajor{_s_nationkey371_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _n_nationkey1270 = (it->second)._n_nationkey1270;
                std::string _n_name1271 = (it->second)._n_name1271;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1271_n{};
                memcpy(_n_name1271_n.data(), (_n_name1271).data(), (_n_name1271).length());
                int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 0);
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 1);
                int32_t _l_discount56 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 2);
                int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 3);
                int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_4702_output.getInt32(i, 4);
                tbl_JOIN_INNER_TD_3840_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 3, _n_name1271_n);
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 0, _o_orderdate231);
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 1, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3840_output.setInt32(r, 2, _l_discount56);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3840_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_3840_output #Row: " << tbl_JOIN_INNER_TD_3840_output.getNumRow() << std::endl;
}

void SW_Project_TD_2676(Table &tbl_JOIN_INNER_TD_3840_output, Table &tbl_Project_TD_2676_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(cast((cast(o_orderdate#231 as double) / 10000.0) as int) AS o_year#1262, (l_extendedprice#55 * (100 - l_discount#56)) AS volume#1263, n_name#1271 AS nation#1264)
    // Input: ListBuffer(o_orderdate#231, l_extendedprice#55, l_discount#56, n_name#1271)
    // Output: ListBuffer(o_year#1262, volume#1263, nation#1264)
    int nrow1 = tbl_JOIN_INNER_TD_3840_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_3840_output.getInt32(i, 0);
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_3840_output.getInt32(i, 1);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_3840_output.getInt32(i, 2);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name1271 = tbl_JOIN_INNER_TD_3840_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 3);
        int32_t _o_year1262 = (_o_orderdate231 / 10000.0);
        tbl_Project_TD_2676_output.setInt32(i, 0, _o_year1262);
        int32_t _volume1263 = (_l_extendedprice55 * (100 - _l_discount56));
        tbl_Project_TD_2676_output.setInt32(i, 1, _volume1263);
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1264 = _n_name1271;
        tbl_Project_TD_2676_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2, _nation1264);
    }
    tbl_Project_TD_2676_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_2676_output #Row: " << tbl_Project_TD_2676_output.getNumRow() << std::endl;
}

typedef int32_t SW_Aggregate_TD_1736_key;
struct SW_Aggregate_TD_1736_payload {
    int64_t _mkt_share1265_sum_0;
    int64_t _mkt_share1265_sum_1;
};
void SW_Aggregate_TD_1736(Table &tbl_Project_TD_2676_output, Table &tbl_Aggregate_TD_1736_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(o_year#1262, (cast(sum(CASE WHEN (nation#1264 = IRAQ) THEN volume#1263 ELSE 0 END) as double) / cast(sum(volume#1263) as double)) AS mkt_share#1265)
    // Input: ListBuffer(o_year#1262, volume#1263, nation#1264)
    // Output: ListBuffer(o_year#1262, mkt_share#1265)
    std::unordered_map<SW_Aggregate_TD_1736_key, SW_Aggregate_TD_1736_payload> ht1;
    int nrow1 = tbl_Project_TD_2676_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_year1262 = tbl_Project_TD_2676_output.getInt32(i, 0);
        int32_t _volume1263 = tbl_Project_TD_2676_output.getInt32(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1264 = tbl_Project_TD_2676_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        SW_Aggregate_TD_1736_key k = _o_year1262;
        int64_t _mkt_share1265_sum_0 = (std::string(_nation1264.data()) == "IRAQ") ? _volume1263 : 0;
        int64_t _mkt_share1265_sum_1 = _volume1263;
        SW_Aggregate_TD_1736_payload p{_mkt_share1265_sum_0, _mkt_share1265_sum_1};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._mkt_share1265_sum_0 + _mkt_share1265_sum_0;
            p._mkt_share1265_sum_0 = sum_0;
            int64_t sum_1 = (it->second)._mkt_share1265_sum_1 + _mkt_share1265_sum_1;
            p._mkt_share1265_sum_1 = sum_1;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        tbl_Aggregate_TD_1736_output.setInt32(r, 0, (it.first));
        int64_t _mkt_share1265 = ((it.second)._mkt_share1265_sum_0 / (it.second)._mkt_share1265_sum_1);
        tbl_Aggregate_TD_1736_output.setInt64(r, 1, _mkt_share1265);
        ++r;
    }
    tbl_Aggregate_TD_1736_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1736_output #Row: " << tbl_Aggregate_TD_1736_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0545(Table &tbl_Aggregate_TD_1736_output, Table &tbl_Sort_TD_0545_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(o_year#1262 ASC NULLS FIRST)
    // Input: ListBuffer(o_year#1262, mkt_share#1265)
    // Output: ListBuffer(o_year#1262, mkt_share#1265)
    struct SW_Sort_TD_0545Row {
        int32_t _o_year1262;
        int64_t _mkt_share1265;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0545Row& a, const SW_Sort_TD_0545Row& b) const { return 
 (a._o_year1262 < b._o_year1262); 
}
    }SW_Sort_TD_0545_order; 

    int nrow1 = tbl_Aggregate_TD_1736_output.getNumRow();
    std::vector<SW_Sort_TD_0545Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_year1262 = tbl_Aggregate_TD_1736_output.getInt32(i, 0);
        int64_t _mkt_share1265 = tbl_Aggregate_TD_1736_output.getInt64(i, 1);
        SW_Sort_TD_0545Row t = {_o_year1262,_mkt_share1265};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0545_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0545_output.setInt32(r, 0, it._o_year1262);
        tbl_Sort_TD_0545_output.setInt64(r, 1, it._mkt_share1265);
        if (r < 10) {
            std::cout << it._o_year1262 << " " << it._mkt_share1265 << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0545_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0545_output #Row: " << tbl_Sort_TD_0545_output.getNumRow() << std::endl;
}

