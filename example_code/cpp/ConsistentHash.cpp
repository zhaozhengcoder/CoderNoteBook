#include <bits/stdc++.h>

using namespace std;

class ConsistentHash
{
private:
    unordered_set<string> physicalServer; // 真实的物理机器
    map<std::size_t, string> serverNodes; // hash 值和节点ip映射（真实ip）
    int virtualNodeNum;
    hash<string> hashStr; // 自带的 hash 函数 生成一个范围是size_t内的数值

public:
    ConsistentHash(int vnum) : virtualNodeNum(vnum){};
    void addNode(const string &ip)
    {
        physicalServer.insert(ip);
        // 加入物理节点的时候也加入虚拟节点
        for (int i = 0; i < virtualNodeNum; ++i)
        {
            stringstream key;
            key << ip << "#" << i;
            serverNodes.insert({hashStr(key.str()), ip});
        }
    }

    void delNode(const string &ip)
    {
        physicalServer.erase(ip);
        for (int i = 0; i < virtualNodeNum; ++i)
        {
            stringstream key;
            key << ip << "#" << i;
            serverNodes.erase(hashStr(key.str()));
        }
    }

    // 模拟插入整数到 hash string
    string virtualInsert(int data)
    {
        stringstream key;
        key << data;
        size_t hashKey = hashStr(key.str());
        // map::lower_bound(key) : 返回map中第一个大于或等于key的迭代器指针
        auto iter = serverNodes.lower_bound(hashKey);  
        if (iter == serverNodes.end())
        {
            return serverNodes.begin()->second;
        }
        return iter->second;
    }
};

// g++ ConsistentHash.c -std=c++11
// 网上随便找了一个代码 
int main()
{
    // 每个节点生成10个虚拟节点
    ConsistentHash hash(10);
    hash.addNode("127.0.0.1");
    hash.addNode("127.0.0.2");
    hash.addNode("127.0.0.3");

    map<string, int> stats;
    for (int i = 0; i < 1000; ++i)
    {
        stats[hash.virtualInsert(i)]++;
    }

    for (auto &s : stats)
    {
        cout << s.first << " " << setprecision(2) << s.second / (1000 * 1.0) << endl;
    }
    return 0;
}