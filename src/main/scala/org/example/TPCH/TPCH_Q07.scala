
package org.example
import org.apache.spark.sql._

/**
 * TPC-H Query 07
 */
class TPCH_Q07 extends TPCH_Queries {

  override def TPCH_execute(sc: SparkSession, schemaProvider: TpchSchemaProvider): DataFrame = {

    // Original Version
    sc.sql("select supp_nation, cust_nation, l_year, sum(volume) as revenue " +
      "from ( select n1.n_name as supp_nation, n2.n_name as cust_nation, int(l_shipdate/10000) as l_year,l_extendedprice * (100 - l_discount) as volume " +
      "from supplier, lineitem, orders, customer, nation n1, nation n2 " +
      "where s_suppkey = l_suppkey " +
      "and o_orderkey = l_orderkey " +
      "and c_custkey = o_custkey " +
      "and s_nationkey = n1.n_nationkey " +
      "and c_nationkey = n2.n_nationkey " +
      "and ((n1.n_name = 'FRANCE' and n2.n_name = 'IRAQ') or (n1.n_name = 'IRAQ' and n2.n_name = 'FRANCE')) " +
      "and l_shipdate between 19950101 and 19961231)" +
      "as shipping " +
      "group by supp_nation, cust_nation, l_year " +
      "order by supp_nation, cust_nation, l_year")

//    sc.sql("select supp_nation, cust_nation, l_year, sum(volume) as revenue " +
//      "from ( select n1.n_name as supp_nation, n2.n_name as cust_nation, int(l_shipdate/10000) as l_year,l_extendedprice * (100 - l_discount) as volume " +
//              "from supplier, lineitem, order, customer, nation n1, nation n2 " +
//              "where s_suppkey = l_suppkey " +
//              "and o_orderkey = l_orderkey " +
//              "and c_custkey = o_custkey " +
//              "and s_nationkey = n1.n_nationkey " +
//              "and c_nationkey = n2.n_nationkey " +
//              "and (n1.n_name = 'FRANCE' or n1.n_name = 'IRAQ') " +
//              "and (n2.n_name = 'FRANCE' or n2.n_name = 'IRAQ') " +
//              "and n1.n_name != n2.n_name " +
//              "and l_shipdate between 19950101 and 19961231)" +
//      "as shipping " +
//      "group by supp_nation, cust_nation, l_year " +
//      "order by supp_nation, cust_nation, l_year")

  }
}
