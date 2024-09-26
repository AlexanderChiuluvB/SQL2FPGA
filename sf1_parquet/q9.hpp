#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_8914(Table &tbl_SerializeFromObject_TD_9157_input, Table &tbl_Filter_TD_8914_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(p_name#285) AND Contains(p_name#285, magenta)))
    // Input: ListBuffer(p_partkey#284, p_name#285)
    // Output: ListBuffer(p_partkey#284)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_9157_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_name285 = tbl_SerializeFromObject_TD_9157_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_p_name285.data()).find("magenta")!=std::string::npos)) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_9157_input.getInt32(i, 0);
            tbl_Filter_TD_8914_output.setInt32(r, 0, _p_partkey284_t);
            r++;
        }
    }
    tbl_Filter_TD_8914_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_8914_output #Row: " << tbl_Filter_TD_8914_output.getNumRow() << std::endl;
}





struct SW_JOIN_INNER_TD_3148_key_leftMajor {
    int32_t _s_nationkey371;
    bool operator==(const SW_JOIN_INNER_TD_3148_key_leftMajor& other) const {
        return ((_s_nationkey371 == other._s_nationkey371));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3148_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3148_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._s_nationkey371));
    }
};
}
struct SW_JOIN_INNER_TD_3148_payload_leftMajor {
    int32_t _l_quantity54;
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
    int32_t _s_nationkey371;
    int32_t _ps_supplycost332;
    int32_t _o_orderdate231;
};
struct SW_JOIN_INNER_TD_3148_key_rightMajor {
    int32_t _n_nationkey164;
    bool operator==(const SW_JOIN_INNER_TD_3148_key_rightMajor& other) const {
        return ((_n_nationkey164 == other._n_nationkey164));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3148_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3148_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_nationkey164));
    }
};
}
struct SW_JOIN_INNER_TD_3148_payload_rightMajor {
    int32_t _n_nationkey164;
    std::string _n_name165;
};
void SW_JOIN_INNER_TD_3148(Table &tbl_JOIN_INNER_TD_4762_output, Table &tbl_SerializeFromObject_TD_4825_input, Table &tbl_JOIN_INNER_TD_3148_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((s_nationkey#371 = n_nationkey#164))
    // Left Table: ListBuffer(l_quantity#54, l_extendedprice#55, l_discount#56, s_nationkey#371, ps_supplycost#332, o_orderdate#231)
    // Right Table: ListBuffer(n_nationkey#164, n_name#165)
    // Output Table: ListBuffer(n_name#165, o_orderdate#231, l_extendedprice#55, l_discount#56, ps_supplycost#332, l_quantity#54)
    int left_nrow = tbl_JOIN_INNER_TD_4762_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_4825_input.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3148_key_leftMajor, SW_JOIN_INNER_TD_3148_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_4762_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_3148_key_leftMajor keyA{_s_nationkey371_k};
            int32_t _l_quantity54 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 0);
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 1);
            int32_t _l_discount56 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 2);
            int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 3);
            int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 4);
            int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 5);
            SW_JOIN_INNER_TD_3148_payload_leftMajor payloadA{_l_quantity54, _l_extendedprice55, _l_discount56, _s_nationkey371, _ps_supplycost332, _o_orderdate231};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_4825_input.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_4825_input.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3148_key_leftMajor{_n_nationkey164_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_quantity54 = (it->second)._l_quantity54;
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _s_nationkey371 = (it->second)._s_nationkey371;
                int32_t _ps_supplycost332 = (it->second)._ps_supplycost332;
                int32_t _o_orderdate231 = (it->second)._o_orderdate231;
                int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_4825_input.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_4825_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _n_name165 = std::string(_n_name165_n.data());
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 5, _l_quantity54);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 2, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 3, _l_discount56);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 4, _ps_supplycost332);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 1, _o_orderdate231);
                tbl_JOIN_INNER_TD_3148_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _n_name165_n);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3148_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3148_key_rightMajor, SW_JOIN_INNER_TD_3148_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_4825_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_4825_input.getInt32(i, 0);
            SW_JOIN_INNER_TD_3148_key_rightMajor keyA{_n_nationkey164_k};
            int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_4825_input.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_4825_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _n_name165 = std::string(_n_name165_n.data());
            SW_JOIN_INNER_TD_3148_payload_rightMajor payloadA{_n_nationkey164, _n_name165};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_4762_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 3);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3148_key_rightMajor{_s_nationkey371_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _n_nationkey164 = (it->second)._n_nationkey164;
                std::string _n_name165 = (it->second)._n_name165;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n{};
                memcpy(_n_name165_n.data(), (_n_name165).data(), (_n_name165).length());
                int32_t _l_quantity54 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 0);
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 1);
                int32_t _l_discount56 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 2);
                int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 3);
                int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 4);
                int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_4762_output.getInt32(i, 5);
                tbl_JOIN_INNER_TD_3148_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _n_name165_n);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 5, _l_quantity54);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 2, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 3, _l_discount56);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 4, _ps_supplycost332);
                tbl_JOIN_INNER_TD_3148_output.setInt32(r, 1, _o_orderdate231);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3148_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_3148_output #Row: " << tbl_JOIN_INNER_TD_3148_output.getNumRow() << std::endl;
}

void SW_Project_TD_2468(Table &tbl_JOIN_INNER_TD_3148_output, Table &tbl_Project_TD_2468_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Project
    // Operation: ListBuffer(n_name#165 AS nation#1362, cast((cast(o_orderdate#231 as double) / 10000.0) as int) AS o_year#1363, ((l_extendedprice#55 * (1 - l_discount#56)) - (ps_supplycost#332 * l_quantity#54)) AS amount#1364)
    // Input: ListBuffer(n_name#165, o_orderdate#231, l_extendedprice#55, l_discount#56, ps_supplycost#332, l_quantity#54)
    // Output: ListBuffer(nation#1362, o_year#1363, amount#1364)
    int nrow1 = tbl_JOIN_INNER_TD_3148_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_JOIN_INNER_TD_3148_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0);
        int32_t _o_orderdate231 = tbl_JOIN_INNER_TD_3148_output.getInt32(i, 1);
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_3148_output.getInt32(i, 2);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_3148_output.getInt32(i, 3);
        int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_3148_output.getInt32(i, 4);
        int32_t _l_quantity54 = tbl_JOIN_INNER_TD_3148_output.getInt32(i, 5);
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1362 = _n_name165;
        tbl_Project_TD_2468_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0, _nation1362);
        int32_t _o_year1363 = (_o_orderdate231 / 10000.0);
        tbl_Project_TD_2468_output.setInt32(i, 1, _o_year1363);
        int32_t _amount1364 = ((_l_extendedprice55 * (1 - _l_discount56)) - (_ps_supplycost332 * _l_quantity54));
        tbl_Project_TD_2468_output.setInt32(i, 2, _amount1364);
    }
    tbl_Project_TD_2468_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_2468_output #Row: " << tbl_Project_TD_2468_output.getNumRow() << std::endl;
}

struct SW_Aggregate_TD_1229_key {
    std::string _nation1362;
    int32_t _o_year1363;
    bool operator==(const SW_Aggregate_TD_1229_key& other) const { return (_nation1362 == other._nation1362) && (_o_year1363 == other._o_year1363); }
};
namespace std {
template <>
struct hash<SW_Aggregate_TD_1229_key> {
    std::size_t operator() (const SW_Aggregate_TD_1229_key& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<string>()(k._nation1362)) + (hash<int32_t>()(k._o_year1363));
    }
};
}
struct SW_Aggregate_TD_1229_payload {
    int64_t _sum_profit1365L_sum_0;
};
void SW_Aggregate_TD_1229(Table &tbl_Project_TD_2468_output, Table &tbl_Aggregate_TD_1229_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(nation#1362, o_year#1363, sum(amount#1364) AS sum_profit#1365L)
    // Input: ListBuffer(nation#1362, o_year#1363, amount#1364)
    // Output: ListBuffer(nation#1362, o_year#1363, sum_profit#1365L)
    std::unordered_map<SW_Aggregate_TD_1229_key, SW_Aggregate_TD_1229_payload> ht1;
    int nrow1 = tbl_Project_TD_2468_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1362 = tbl_Project_TD_2468_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0);
        int32_t _o_year1363 = tbl_Project_TD_2468_output.getInt32(i, 1);
        int32_t _amount1364 = tbl_Project_TD_2468_output.getInt32(i, 2);
        SW_Aggregate_TD_1229_key k{std::string(_nation1362.data()), _o_year1363};
        int64_t _sum_profit1365L_sum_0 = _amount1364;
        SW_Aggregate_TD_1229_payload p{_sum_profit1365L_sum_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._sum_profit1365L_sum_0 + _sum_profit1365L_sum_0;
            p._sum_profit1365L_sum_0 = sum_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1362{};
        memcpy(_nation1362.data(), ((it.first)._nation1362).data(), ((it.first)._nation1362).length());
        tbl_Aggregate_TD_1229_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _nation1362);
        tbl_Aggregate_TD_1229_output.setInt32(r, 1, (it.first)._o_year1363);
        int64_t _sum_profit1365L = (it.second)._sum_profit1365L_sum_0;
        tbl_Aggregate_TD_1229_output.setInt64(r, 2, _sum_profit1365L);
        ++r;
    }
    tbl_Aggregate_TD_1229_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1229_output #Row: " << tbl_Aggregate_TD_1229_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0522(Table &tbl_Aggregate_TD_1229_output, Table &tbl_Sort_TD_0522_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(nation#1362 ASC NULLS FIRST, o_year#1363 DESC NULLS LAST)
    // Input: ListBuffer(nation#1362, o_year#1363, sum_profit#1365L)
    // Output: ListBuffer(nation#1362, o_year#1363, sum_profit#1365L)
    struct SW_Sort_TD_0522Row {
        std::string _nation1362;
        int32_t _o_year1363;
        int64_t _sum_profit1365L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0522Row& a, const SW_Sort_TD_0522Row& b) const { return 
 (a._nation1362 < b._nation1362) || 
 ((a._nation1362 == b._nation1362) && (a._o_year1363 > b._o_year1363)); 
}
    }SW_Sort_TD_0522_order; 

    int nrow1 = tbl_Aggregate_TD_1229_output.getNumRow();
    std::vector<SW_Sort_TD_0522Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1362 = tbl_Aggregate_TD_1229_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int32_t _o_year1363 = tbl_Aggregate_TD_1229_output.getInt32(i, 1);
        int64_t _sum_profit1365L = tbl_Aggregate_TD_1229_output.getInt64(i, 2);
        SW_Sort_TD_0522Row t = {std::string(_nation1362.data()),_o_year1363,_sum_profit1365L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0522_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _nation1362{};
        memcpy(_nation1362.data(), (it._nation1362).data(), (it._nation1362).length());
        tbl_Sort_TD_0522_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _nation1362);
        tbl_Sort_TD_0522_output.setInt32(r, 1, it._o_year1363);
        tbl_Sort_TD_0522_output.setInt64(r, 2, it._sum_profit1365L);
        if (r < 10) {
            std::cout << (it._nation1362).data() << " " << it._o_year1363 << " " << it._sum_profit1365L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0522_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0522_output #Row: " << tbl_Sort_TD_0522_output.getNumRow() << std::endl;
}

