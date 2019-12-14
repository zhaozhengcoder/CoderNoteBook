# redis 集群搭建

## 目录

* [redis集群搭建](#redis集群搭建)

* [redis主从/哨兵/集群的原理分析](#redis主从/哨兵/集群的原理分析)

---

## redis集群搭建

1. 安装redis
    ```
    sudo apt-get isntall redis-server
    ```

2. redis启动多个实例
    ```
    # 1. redis 的配置文件
    /etc/redis/redis.conf

    # 2. redis 拷贝一份
    cp /etc/redis/redis.conf ~/redis_conf/. 
    ```

3. 修改为多分的配置文件
    ```
    $ ll
    total 360K
    -rwxrwxrwx 1 root       root       58K Dec  7 12:20 redis_7000.conf
    -rwxrwxr-x 1 harleyzhao harleyzhao 58K Dec  7 12:23 redis_7001.conf
    -rwxrwxr-x 1 harleyzhao harleyzhao 58K Dec  7 12:23 redis_7002.conf
    -rwxrwxr-x 1 harleyzhao harleyzhao 58K Dec  7 12:23 redis_7003.conf
    -rwxrwxr-x 1 harleyzhao harleyzhao 58K Dec  7 12:24 redis_7004.conf
    -rwxrwxr-x 1 harleyzhao harleyzhao 58K Dec  7 12:24 redis_7005.conf
    ```

4. 修改配置文件
    ```
    port 7000
    #deamonize yes  #后台启动
    cluster-enabled yes
    cluster-config-file nodes_7000.conf
    cluster-node-timeout 5000
    appendonly yes
    ```

    提供一个实例配置文件： 
    
    >(redis_7000.conf)[../example_code/redis_conf/redis_7000.conf]

5. 启动单个redis实例
    ```
    sudo redis-server redis_7001.conf
    ...
    sudo redis-server redis_7005.conf

    $ ps -ef | grep redis
    root       502     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7000 [
    root       519     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7001 [
    root       536     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7002 [
    root       553     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7003 [
    root       570     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7004 [
    root       587     1  0 14:28 ?        00:00:00 redis-server 127.0.0.1:7005 [
    ```

6. 查看redis-cli
    ```
    $ redis-cli -c -p 7000
    127.0.0.1:7000> cluster info
    cluster_state:fail
    cluster_slots_assigned:0
    cluster_slots_ok:0
    cluster_slots_pfail:0
    cluster_slots_fail:0
    cluster_known_nodes:1
    cluster_size:0
    cluster_current_epoch:0
    cluster_my_epoch:0
    cluster_stats_messages_sent:0
    cluster_stats_messages_received:0
    127.0.0.1:7000> exit
    ```

7. redis-trib
    ```
    sudo apt-get install ruby-full

    mkdir ~/down && cd ~/down
    wget http://rubygems.org/downloads/redis-3.3.0.gem
    gem install -l redis-3.3.0.gem

    # 找到redis-trib
    sudo find / -name redis-trib.rb

    # redis-trib 管理集群
    $ redis-trib.rb create --replicas 1 127.0.0.1:7000 127.0.0.1:7001 127.0.0.1:7002 127.0.0.1:7003 127.0.0.1:7004 127.0.0.1:7005
    >>> Creating cluster
    >>> Performing hash slots allocation on 6 nodes...
    Using 3 masters:
    127.0.0.1:7000
    127.0.0.1:7001
    127.0.0.1:7002
    Adding replica 127.0.0.1:7004 to 127.0.0.1:7000
    Adding replica 127.0.0.1:7005 to 127.0.0.1:7001
    Adding replica 127.0.0.1:7003 to 127.0.0.1:7002
    >>> Trying to optimize slaves allocation for anti-affinity
    [WARNING] Some slaves are in the same host as their master
    M: d81022ee4427a03e464008c7502e4af521abe845 127.0.0.1:7000
    slots:0-5460 (5461 slots) master
    M: 5c7af37df15107e0fa4f66bd14639e3885c6548d 127.0.0.1:7001
    slots:5461-10922 (5462 slots) master
    M: 7a5735b92963a2942ae94d98974816a62219cd15 127.0.0.1:7002
    slots:10923-16383 (5461 slots) master
    S: 041724d3c83350f8937c754ee9e1bfe9072e39ad 127.0.0.1:7003
    replicates d81022ee4427a03e464008c7502e4af521abe845
    S: 2d0f535e8ea4364c84bf3ae150cb563a784620a2 127.0.0.1:7004
    replicates 5c7af37df15107e0fa4f66bd14639e3885c6548d
    S: 69ca8f5a32e8288f71116b8d06787fa77d6daecf 127.0.0.1:7005
    replicates 7a5735b92963a2942ae94d98974816a62219cd15
    Can I set the above configuration? (type 'yes' to accept): yes
    >>> Nodes configuration updated
    >>> Assign a different config epoch to each node
    >>> Sending CLUSTER MEET messages to join the cluster
    Waiting for the cluster to join...
    >>> Performing Cluster Check (using node 127.0.0.1:7000)
    M: d81022ee4427a03e464008c7502e4af521abe845 127.0.0.1:7000
    slots:0-5460 (5461 slots) master
    1 additional replica(s)
    M: 7a5735b92963a2942ae94d98974816a62219cd15 127.0.0.1:7002
    slots:10923-16383 (5461 slots) master
    1 additional replica(s)
    S: 69ca8f5a32e8288f71116b8d06787fa77d6daecf 127.0.0.1:7005
    slots: (0 slots) slave
    replicates 7a5735b92963a2942ae94d98974816a62219cd15
    S: 2d0f535e8ea4364c84bf3ae150cb563a784620a2 127.0.0.1:7004
    slots: (0 slots) slave
    replicates 5c7af37df15107e0fa4f66bd14639e3885c6548d
    M: 5c7af37df15107e0fa4f66bd14639e3885c6548d 127.0.0.1:7001
    slots:5461-10922 (5462 slots) master
    1 additional replica(s)
    S: 041724d3c83350f8937c754ee9e1bfe9072e39ad 127.0.0.1:7003
    slots: (0 slots) slave
    replicates d81022ee4427a03e464008c7502e4af521abe845
    [OK] All nodes agree about slots configuration.
    >>> Check for open slots...
    >>> Check slots coverage...
    [OK] All 16384 slots covered.
    ```

8. 集群搭建成功

    如果存入一个值，按照redis cluster哈希槽的算法： CRC16('key')%16384 = 6782。 那么就会把这个key 的存储分配到 B 上了。同样，当我连接
    (A,B,C)任何一个节点想获取'key'这个key时，也会这样的算法，然后内部跳转到B节点上获取数据

    设置一个key
    ```
    $ redis-cli -c -p 7000
    127.0.0.1:7000> set test_cluster "hello_7000"
    OK
    127.0.0.1:7000> keys *
    1) "test_cluster"
    127.0.0.1:7000> cluster info
    cluster_state:ok
    cluster_slots_assigned:16384
    cluster_slots_ok:16384
    cluster_slots_pfail:0
    cluster_slots_fail:0
    cluster_known_nodes:6
    cluster_size:3
    cluster_current_epoch:6
    cluster_my_epoch:1
    cluster_stats_messages_ping_sent:4507
    cluster_stats_messages_pong_sent:4427
    cluster_stats_messages_sent:8934
    cluster_stats_messages_ping_received:4422
    cluster_stats_messages_pong_received:4507
    cluster_stats_messages_meet_received:5
    cluster_stats_messages_received:8934
    ```

    查找一个key
    ```
    $ redis-cli -c -p 7001
    127.0.0.1:7001> keys*
    (error) ERR unknown command 'keys*'
    127.0.0.1:7001> keys *
    (empty list or set)
    127.0.0.1:7001> get test_cluster
    -> Redirected to slot [5056] located at 127.0.0.1:7000
    "hello_7000"
    127.0.0.1:7000> 
    ```

## redis主从/哨兵/集群的原理分析

1. redis-cluster client 的原理

    http://ralphbupt.github.io/2017/03/08/redis-cluster/

## 参考
0. redis 命令文档： http://redisdoc.com/topic/cluster-tutorial.html

1. 腾讯云 ： https://cloud.tencent.com/developer/article/1432088

2. redis-trib.rb 搭建 Redis Cluster ： https://www.jianshu.com/p/6b85a004531f

3. https://www.cnblogs.com/kevingrace/p/7910692.html