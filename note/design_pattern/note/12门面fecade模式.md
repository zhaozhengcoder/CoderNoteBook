## 门面Fecade模式

门面模式很像一个中介，帮client把一些逻辑隐藏起来，对外提供简洁的接口。其实，这个不仅仅是一个设计模式，更多的表现的是设计的分层。

```
{
    WORKER work;

    work.init();
    work.load();
    work.do();
}
```


```
class FECADE
{
    int do()
    {
        work->init();
        work->load();
        work->do();
    }
};

{
    WORKER work;
    FECADE fecade(work);

    // 
    fecade.do();
}
```