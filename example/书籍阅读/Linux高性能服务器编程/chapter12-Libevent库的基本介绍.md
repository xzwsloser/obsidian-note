1.  `Libevent`库基本编程方式:
![[Pasted image 20250114203307.png]]
2. `Libevent`库的核心组件:
![[Pasted image 20250114203350.png]]
其中各个组件的作用以及在`Libevent`库中的实现如下:
- `Reactor`: 用于管理各种事件,并且利用 `IO` 多路复用技术来实现事件的分发操作,比如把监听到的事件分发给绑定的事件处理,表现形式就是`event_base`对象,同时具有注册事件和删除事件的功能
- `EventDemultiplexer`:  相当于`Reactor` 的底层的事件分发器把各个系统它中的`IO`多路复用封装成同一个接口给`Reactor`使用
- `EventHandler`: 事件处理器对象(其实可以成为事件对象),可以利用注册函数添加相应的回调函数和参数,在`Libevent`库中的实现就是`event`对象,包含三种`event`对象,分别为`IO`事件处理器,定时器事件处理器,信号处理函数等事件(核心就是`event_new`函数)
- `ConcreteEventHandler`: 具体的事件处理器对象
3. `Libevent`库各个组件之间的交互时序图:
![[Pasted image 20250114204622.png]]
> 如上就是`Libevent`库中的各种基本组件以及之间的关系,关于其中更加详细的内容比如定时器的数据结构,`Reactor`用于管理各种事件处理器的数据结构等细节这里不做解释,之后阅读源代码的时候再看一下
