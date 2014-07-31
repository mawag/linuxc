typedef struct
{
	int			detachstate;	//新线程是否与进程中其他线程脱离同步
	int			schedpolicy;	//线程调度策略
						//主要包括3种，
							SCHED_OTHER（正常、非实时）
							SCHED_RR（实时、轮转法）
							SCHED_FIFO（实时、先入先出）
						缺省为SCHED_OTHER，后两种调度策略仅对超级用户有效.
	struct sched_param	schedparam;	//线程的调度参数
						//sched_priority整型变量表示线程的运行优先级,仅当调度策略为实时
	int			inheritsched;	//线程的继承性
	int			scope;		//线程的作用域
	size_t			guardsize;	//线程栈末尾的警戒缓冲区大小
	int			stackaddr_set;	//堆栈的地址集
	void			*stackaddr;	//线程堆栈的位置
	size_t			stacksize;	//线程堆栈的大小
}pthread_attr_t;
