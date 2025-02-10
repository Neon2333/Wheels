/*
	ver1.0
*/
//#include <iostream> 
//#include <mutex>
//#include <queue>
//#include <vector>
//#include <functional>
//#include <condition_variable>
//#include <atomic>
//#include <chrono>
//
//class ThreadPool
//{
//public:
//	ThreadPool(int num)
//	{
//		stopAll = false;	//线程池对象停止标志
//		m_numThreads = num < 1 ? 1 : num;	//最少1个线程
//		
//		for (int i = 0; i < m_numThreads; i++)
//		{
//			m_threads.emplace_back([=]() {	//emplace_back移动语义，不拷贝
//				while (true)	
//				{
//					std::unique_lock<std::mutex> ul(mtx);	//互斥锁，锁住对共享变量m_tasks的访问
//					cv.wait(ul, [=]() {						//条件变量控制锁ul的释放、线程的阻塞和继续
//						return !m_tasks.empty() || stopAll;	//任务队列非空或线程池停止则不阻塞，拿到ul
//						});
//					if (stopAll == true && m_tasks.empty())	//如果线程池停止线程立即return终止
//					{
//						return;
//					}
//					std::function<void()> task(std::move(m_tasks.front()));	//从头部取任务，移动语义减少拷贝，可调用对象包装器包装
//					m_tasks.pop();	//任务队列弹出
//					std::cout << "threadID=" << std::this_thread::get_id() << ",start working..." << std::endl;	
//					ul.unlock();	//任务队列访问结束，解锁放掉ul
//					
//					task();	//线程执行任务
//					ul.lock();
//					std::cout << "threadID=" << std::this_thread::get_id() << ",end working..." << std::endl;	//线程执行完任务日志输出
//					ul.unlock();
//				}
//				});
//		}
//	}
//	ThreadPool(ThreadPool& another) = delete;	//禁用拷贝
//	ThreadPool& operator=(ThreadPool& another) = delete;	//禁用operator=
//	~ThreadPool()
//	{
//		//析构销毁线程池，释放资源
//		std::unique_lock<std::mutex> ul(mtx);	//要访问共享变量stopAll（多个线程都访问了stopAll)，上锁
//		stopAll = true;	//线程池停止标志置true
//		ul.unlock();	//stopAll访问结束，解锁
//		cv.notify_all();	//线程池要销毁了。通知所有线程全部不阻塞向下执行
//		for (auto& item : m_threads)
//		{
//			item.join();	//等待全部线程return终止
//		}
//	}
//
//	//主线程添加任务。生产者
//	template<typename F, typename... Args>
//	void addTask(F&& f, Args&&... args)	//万能引用
//	{
//		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	//f和args是万能引用需要完美转发，通过bind把参数绑定到函数f上
//		//局部作用域，限定互斥锁ul锁定范围
//		{
//			std::unique_lock<std::mutex> ul(mtx);	//要访问共享变量m_tasks，上锁
//			m_tasks.emplace(std::move(task));		//任务队列里放1个任务，移动语义避免拷贝
//		}
//		cv.notify_one();	//放了个任务，解除1个线程的阻塞向下执行任务
//	}
//
//private:
//	std::mutex mtx;	//互斥量
//	std::condition_variable cv;	//条件变量
//	bool stopAll;
//	int m_numThreads;	//线程数
//	std::queue<std::function<void()>> m_tasks;	//任务队列。bind绑定了参数，所以function的模版类型是void()
//	std::vector<std::thread> m_threads;	//线程容器
//};
//
//
//std::mutex mtxfunc;
//int data;
//void func()
//{
//	for (int i = 0; i < 1000000; i++)
//	{
//		std::unique_lock<std::mutex> ul(mtxfunc);
//		data++;
//	}
//}
//
//int main()
//{
//	auto start1 = std::chrono::steady_clock::now();
//	ThreadPool* tp = new ThreadPool(6);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	delete tp;
//	auto end1 = std::chrono::steady_clock::now();
//	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << data << std::endl;
//
//	auto start2 = std::chrono::steady_clock::now();
//	std::cout << "pool spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "ms" << std::endl;
//	for (int i = 0; i < 6000000; i++)
//	{
//		data++;
//	}
//	auto end2 = std::chrono::steady_clock::now();
//	std::cout << "mainthread spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << "ms" << std::endl;
//}



/*
	Ver2.0
	用2个锁mtxPool锁其他属性，mtxTask锁子线程内部操作还是不太可行。因为子线程内部不仅仅涉及m_tasks的访问，也有m_threads的访问
	还有一些属性的访问。如果用mtxTask把整个子线程任务都锁住，明显临界区太大，线程不好切换，效率降低。
*/
//#include <iostream> 
//#include <mutex>
//#include <queue>
//#include <vector>
//#include <functional>
//#include <condition_variable>
//#include <atomic>
//#include <chrono>
//
//class ThreadPool
//{
//private:
//	std::queue<std::function<void()>> m_tasks;	//任务队列。bind绑定了参数，所以function的模版类型是void()
//	std::vector<std::thread> m_threads;			//线程容器
//	//std::vector<std::thread> m_exitedThreads;	//暂存已退出线程池的线程
//
//	std::condition_variable cvTasksNotEmpty;	//条件变量，任务队列非空获得锁
//	std::mutex mtxTask;			//子线程执行任务时保护共享属性的锁
//	std::mutex mtxPool;			//访问线程池的共享属性的锁
//	std::thread m_threadManagement;	//管理者线程
//
//	bool m_shutdown;			//线程池关闭flag
//	int m_numMinThreads;	//初始线程数
//	int m_numMaxThreads;	//线程最大数
//	int m_numCurThreads;		//当前线程数
//	int m_numBusyThreads;	//当前正在工作的线程数
//	int m_numExitThreads;	//当前要销毁的线程数
//	const int THREADMANAGENUM = 2;	//管理线程一次添加或删除的线程数
//
//public:
//	int getNumThreads() { return m_numCurThreads; }
//
//	int getNumBusyThreads() { return m_numBusyThreads; }
//
//	int getNumExitThreads() { return m_numExitThreads; }
//
//	int getNumMinThreads() { return m_numMinThreads; }
//
//	int getNumMaxThreads() { return m_numMaxThreads; }
//
//public:
//	ThreadPool(int min, int max) :m_threadManagement(ThreadPool::threadManage, this), m_numMinThreads(min < 2 ? 2 : min), m_numMaxThreads(max)
//	{
//		//从最小线程数开始
//		m_shutdown = false;
//		m_numCurThreads = m_numMinThreads;	
//		m_numBusyThreads = 0;
//		m_numExitThreads = 0;
//
//		for (int i = 0; i < m_numCurThreads; i++)
//		{
//			m_threads.emplace_back([this]() {
//				std::unique_lock<std::mutex> ulTask(mtxTask);
//				m_numCurThreads++;
//				ulTask.unlock();
//				threadTask();
//				});
//		}
//	}
//	ThreadPool(ThreadPool& another) = delete;	//禁用拷贝
//	ThreadPool& operator=(ThreadPool& another) = delete;	//禁用operator=
//	~ThreadPool()
//	{
//		//析构销毁线程池，释放资源
//		std::unique_lock<std::mutex> ul(mtxPool);	//要访问共享变量stopAll（多个线程都访问了stopAll)，上锁
//		m_shutdown = true;	//线程池停止标志置true
//		ul.unlock();
//		cvTasksNotEmpty.notify_all();	//线程池要销毁了。通知所有线程全部不阻塞向下执行
//
//		for (auto& item : m_threads)	//不用加锁，访问m_threads的只有主线程和管理者线程，但因为shutdown=true，管理者线程已经不会访问了。
//		{
//			item.join();	//等待全部线程return终止
//		}
//
//		m_threadManagement.join();	//等待管理线程终止
//	}
//
//	//子线程任务
//	void threadTask()
//	{
//		while (true)
//		{
//			std::unique_lock<std::mutex> ulBusy(mtxTask);
//			//任务队列非空或线程池关闭，拿到mtxTask向下执行
//			cvTasksNotEmpty.wait(ulBusy, [=]() {
//				return !m_tasks.empty() || m_shutdown;
//				});
//
//			//判断当前管理者线程是否要减少线程池中线程。这样销毁的线程要从m_threads中去掉。这些线程只能detach，因为没法在析构中join()。
//			//也可以再用个vector<std::thread>存储这些被管理者要销毁的线程，在析构时join()，但是麻烦。
//			if (m_numExitThreads > 0)
//			{
//				m_numExitThreads--;
//				if (m_numCurThreads > m_numMinThreads)
//				{
//					m_numCurThreads--;
//					//关闭当前线程
//					for (auto iter = m_threads.begin(); iter != m_threads.end();)
//					{
//						if (iter->get_id() == std::this_thread::get_id())
//						{
//							//m_exitedThreads.emplace_back(std::move(*iter));	
//							iter->detach();
//							iter = m_threads.erase(iter);
//						}
//						else
//						{
//							iter++;
//						}
//					}
//					return;
//				}
//
//			}
//
//			//判断是否线程池被关闭，管理者线程不工作。m_threads中线程数固定，在析构中全部都要join()，闲置线程直接return终止
//			if (m_shutdown == true && m_tasks.empty())
//			{
//				return;
//			}
//
//			//取任务执行
//			std::function<void()> task(std::move(m_tasks.front()));
//			m_tasks.pop();
//			m_numBusyThreads++;
//			ulBusy.unlock();	//手动释放cvTasksNotEmpty拿到的锁
//			std::cout << "threadID=" << std::this_thread::get_id() << ",start working..." << std::endl;
//
//			task();	//线程执行任务
//
//			ulBusy.lock();
//			m_numBusyThreads--;
//			ulBusy.unlock();
//			std::cout << "threadID=" << std::this_thread::get_id() << ",end working..." << std::endl;	//线程执行完任务日志输出
//		}
//	}
//
//	//主线程添加任务。生产者
//	template<typename F, typename... Args>
//	void addTask(F&& f, Args&&... args)	//万能引用
//	{
//		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	//f和args是万能引用需要完美转发，通过bind把参数绑定到函数f上
//		//局部作用域，限定互斥锁ul锁定范围
//		{
//			std::unique_lock<std::mutex> ul(mtxPool);	//要访问共享变量m_tasks，上锁
//			m_tasks.emplace(std::move(task));		//任务队列里放1个任务，移动语义避免拷贝
//		}
//		cvTasksNotEmpty.notify_one();	//放了个任务，解除1个线程的阻塞向下执行任务
//	}
//
//	//管理者线程任务
//	static void threadManage(ThreadPool* poolInstance);
//
//};
//
//void ThreadPool::threadManage(ThreadPool* poolInstance)
//{
//	while (!poolInstance->m_shutdown)
//	{
//		std::unique_lock<std::mutex> ulPool(poolInstance->mtxPool);
//
//		std::this_thread::sleep_for(std::chrono::seconds(3));
//
//		int numThreads = poolInstance->getNumThreads();
//		int numMaxThreads = poolInstance->getNumMaxThreads();
//		int numMinThreads = poolInstance->getNumMinThreads();
//		int numTasks = static_cast<int>(poolInstance->m_tasks.size());
//		int numBusyThreads = poolInstance->getNumBusyThreads();
//
//		//加线程
//		if (numThreads < numMaxThreads && numThreads < numTasks)
//		{
//			for (int i = 0; i < poolInstance->THREADMANAGENUM && poolInstance->getNumThreads() < poolInstance->getNumMaxThreads(); i++)
//			{
//				poolInstance->m_threads.emplace_back([poolInstance]() {
//					poolInstance->threadTask();
//					});
//			}
//			poolInstance->m_numCurThreads++;
//		}
//		//减少线程
//		if (numBusyThreads * 2 < numThreads && numThreads > numMinThreads)
//		{
//			poolInstance->m_numExitThreads = poolInstance->THREADMANAGENUM;
//			//通知m_numExitThreads个阻塞的线程向下执行，就会退出
//			for (int i = 0; i < poolInstance->m_numExitThreads; i++)
//			{
//				poolInstance->cvTasksNotEmpty.notify_one();
//			}
//		}
//
//	}
//}
//
//
//std::mutex mtxfunc;
//int data=0;
//void func()
//{
//	std::unique_lock<std::mutex> ul(mtxfunc);
//	for (int i = 0; i < 100000; i++)
//	{
//		data++;
//	}
//}
//
//int main()
//{
//	auto start1 = std::chrono::steady_clock::now();
//	ThreadPool* tp = new ThreadPool(6,10);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//
//	auto end1 = std::chrono::steady_clock::now();
//	delete tp;
//	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << data << std::endl;
//
//	auto start2 = std::chrono::steady_clock::now();
//	std::cout << "pool cost:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "ms" << std::endl;
//
//}



/*
	ver4.0
	给m_threads、m_tasks单独2个锁，其他属性改为原子变量
	读共享变量不加锁，写共享变量加锁
	bug:
		效率比单线程低
	问题：
		主线程不能获知任务什么时候执行完
*/
//#include <iostream> 
//#include <mutex>
//#include <queue>
//#include <vector>
//#include <functional>
//#include <condition_variable>
//#include <atomic>
//#include <chrono>
//
//class ThreadPool
//{
//private:
//	std::queue<std::function<void()>> m_tasks;	//任务队列。bind绑定了参数，所以function的模版类型是void()
//	std::vector<std::thread> m_threads;			//线程容器
//	std::thread m_threadManagement;	//管理者线程
//	//std::vector<std::thread> m_exitedThreads;	//暂存已退出线程池的线程
//
//	std::condition_variable cvTasksNotEmpty;	//条件变量，任务队列非空获得锁
//	std::mutex mtxTasks;
//	std::mutex mtxThreads;
//	std::mutex mtxPoolFields;
//
//	bool m_shutdown;			//线程池关闭flag
//	int m_numMinThreads;	//初始线程数
//	int m_numMaxThreads;	//线程最大数
//	std::atomic<int> m_numCurThreads;		//当前线程数
//	std::atomic<int> m_numBusyThreads;	//当前正在工作的线程数
//	std::atomic<int> m_numExitThreads;	//当前要销毁的线程数
//	const int THREADMANAGENUM = 2;	//管理线程一次添加或删除的线程数
//
//public:
//	int getBusyThreads()
//	{
//		return m_numBusyThreads.load();
//	}
//
//public:
//	ThreadPool(int min, int max) :m_threadManagement(ThreadPool::threadManage, this), m_numMinThreads(min < 1 ? 1 : min), m_numMaxThreads(max)
//	{
//		m_shutdown = false;
//		m_numCurThreads = m_numMinThreads;	//从最小线程数开始
//		m_numBusyThreads = 0;
//		m_numExitThreads = 0;
//
//		for (int i = 0; i < m_numCurThreads; i++)
//		{
//			std::unique_lock<std::mutex> ulThreads(mtxThreads);
//			m_threads.emplace_back([this]() {
//				m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
//				threadTask();
//				});
//		}
//
//
//	}
//	ThreadPool(ThreadPool& another) = delete;	//禁用拷贝
//	ThreadPool& operator=(ThreadPool& another) = delete;	//禁用operator=
//	~ThreadPool()
//	{
//		//析构销毁线程池，释放资源
//		m_shutdown = true;	//线程池停止标志置true
//		cvTasksNotEmpty.notify_all();	//线程池要销毁了。通知所有线程全部不阻塞向下执行
//
//		for (auto& item : m_threads)	//不用加锁，访问m_threads的只有主线程和管理者线程，但因为shutdown=true，管理者线程已经不会访问了。
//		{
//			item.join();	//等待全部线程return终止
//		}
//
//		m_threadManagement.join();	//等待管理线程终止
//	}
//
//	//子线程任务
//	void threadTask()
//	{
//		while (true)
//		{
//			std::unique_lock<std::mutex> ulTasks(mtxTasks);
//			//任务队列非空或线程池关闭，拿到mtxTask向下执行
//			cvTasksNotEmpty.wait(ulTasks, [=]() {
//				return !m_tasks.empty() || m_shutdown;
//				});
//
//			//判断当前管理者线程是否要减少线程池中线程。这样销毁的线程要从m_threads中去掉。这些线程只能detach，因为没法在析构中join()。
//			//也可以再用个vector<std::thread>存储这些被管理者要销毁的线程，在析构时join()，但是麻烦。
//
//			if (m_numExitThreads > 0)
//			{
//				m_numExitThreads.fetch_sub(1, std::memory_order_relaxed);
//				if (m_numCurThreads > m_numMinThreads)
//				{
//					m_numCurThreads.fetch_sub(1, std::memory_order_relaxed);
//					//关闭当前线程
//					for (auto iter = m_threads.begin(); iter != m_threads.end();)
//					{
//						if (iter->get_id() == std::this_thread::get_id())
//						{
//							iter->detach();
//							std::unique_lock<std::mutex> ulThreads(mtxThreads);
//							iter = m_threads.erase(iter);
//						}
//						else
//						{
//							iter++;
//						}
//					}
//					return;
//				}
//
//			}
//
//			//判断是否线程池被关闭，管理者线程不工作。m_threads中线程数固定，在析构中全部都要join()，闲置线程直接return终止
//			if (m_shutdown == true && m_tasks.empty())
//			{
//				return;
//			}
//
//			//取任务执行
//			std::function<void()> task(std::move(m_tasks.front()));
//			m_tasks.pop();
//			std::cout << "threadID=" << std::this_thread::get_id() << ",start working..." << std::endl;
//			ulTasks.unlock();	
//			m_numBusyThreads.fetch_add(1, std::memory_order_relaxed);
//
//			task();	//线程执行任务
//
//			m_numBusyThreads.fetch_sub(1, std::memory_order_relaxed);
//			std::cout << "threadID=" << std::this_thread::get_id() << ",end working..." << std::endl;	//线程执行完任务日志输出
//		}
//	}
//
//	//主线程添加任务。生产者
//	template<typename F, typename... Args>
//	void addTask(F&& f, Args&&... args)	//万能引用
//	{
//		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	//f和args是万能引用需要完美转发，通过bind把参数绑定到函数f上
//		//局部作用域，限定互斥锁ul锁定范围
//		{
//			std::unique_lock<std::mutex> ulTasks(mtxTasks);	//要访问共享变量m_tasks，上锁
//			m_tasks.emplace(std::move(task));		//任务队列里放1个任务，移动语义避免拷贝
//		}
//		cvTasksNotEmpty.notify_one();	//放了个任务，解除1个线程的阻塞向下执行任务
//	}
//
//	//管理者线程任务
//	static void threadManage(ThreadPool* poolInstance);
//
//};
//
//void ThreadPool::threadManage(ThreadPool* poolInstance)
//{
//	while (!poolInstance->m_shutdown)
//	{
//		std::this_thread::sleep_for(std::chrono::seconds(3));
//
//		//如果只是使用共享变量的值而不修改，可以用一个锁集中读取，然后使用。否则这些变量的读取放在代码中，分散开来，不方便上锁、解锁
//		std::unique_lock<std::mutex> ulTasks(poolInstance->mtxTasks);
//		int numTasks = static_cast<int>(poolInstance->m_tasks.size());
//		ulTasks.unlock();
//
//		//加线程
//		if (poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads && poolInstance->m_numCurThreads < numTasks)
//		{
//			for (int i = 0; i < poolInstance->THREADMANAGENUM && poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads; i++)
//			{
//				std::unique_lock<std::mutex> ulThreads(poolInstance->mtxThreads);
//				poolInstance->m_threads.emplace_back([poolInstance]() {
//					poolInstance->threadTask();
//					});
//			}
//			//写共享变量，只能这样加锁、解锁包起来
//			poolInstance->m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
//		}
//		//减少线程
//		if (poolInstance->m_numBusyThreads * 2 < poolInstance->m_numCurThreads && poolInstance->m_numCurThreads > poolInstance->m_numMinThreads)
//		{
//			poolInstance->m_numExitThreads.store(poolInstance->THREADMANAGENUM);
//
//			//通知m_numExitThreads个阻塞的线程向下执行，就会退出
//			for (int i = 0; i < poolInstance->m_numExitThreads; i++)
//			{
//				poolInstance->cvTasksNotEmpty.notify_one();
//			}
//		}
//
//	}
//}
//
//
//std::mutex mtxfunc;
//int data = 0;
//void func()
//{
//	for (int i = 0; i < 1000000; i++)
//	{
//		std::unique_lock<std::mutex> ul(mtxfunc);
//		data++;
//	}
//}
//
//int main()
//{
//	auto start1 = std::chrono::steady_clock::now();
//	ThreadPool* tp = new ThreadPool(6,10);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//	tp->addTask(func);
//
//	auto end1 = std::chrono::steady_clock::now();
//	
//	while (true)
//	{
//		std::cout << "busy threads=" << tp->getBusyThreads() << std::endl;
//		if (tp->getBusyThreads() == 0)
//		{
//			std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << data << std::endl;
//			std::cout << "pool spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "ms" << std::endl;
//		}
//	}
//	delete tp;
//
//
//
//	auto start2 = std::chrono::steady_clock::now();
//	for (int i = 0; i < 10; i++)
//	{
//		data++;
//	}
//	auto end2 = std::chrono::steady_clock::now();
//	std::cout << "mainthread spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << "ms" << std::endl;
//	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << data << std::endl;
//
//}


/*
	ver5.0
	为了解决主线程不知道任务列表何时完成。使用std::packged_task和std::future，让主线程可以通过future.get()阻塞获得返回值
*/
//#include <iostream> 
//#include <mutex>
//#include <queue>
//#include <vector>
//#include <functional>
//#include <condition_variable>
//#include <atomic>
//#include <chrono>
//#include <future>
//
//class ThreadPool
//{
//private:
//	std::queue<std::function<void()>> m_tasks;	//任务队列。bind绑定了参数，所以function的模版类型是void()
//	std::vector<std::thread> m_threads;			//线程容器
//	std::thread m_threadManagement;	//管理者线程
//	//std::vector<std::thread> m_exitedThreads;	//暂存已退出线程池的线程
//
//	std::condition_variable cvTasksNotEmpty;	//条件变量，任务队列非空获得锁
//	std::mutex mtxTasks;
//	std::mutex mtxThreads;
//	std::mutex mtxPoolFields;
//
//	bool m_shutdown;			//线程池关闭flag
//	int m_numMinThreads;	//初始线程数
//	int m_numMaxThreads;	//线程最大数
//	std::atomic<int> m_numCurThreads;		//当前线程数
//	std::atomic<int> m_numBusyThreads;	//当前正在工作的线程数
//	std::atomic<int> m_numExitThreads;	//当前要销毁的线程数
//	const int THREADMANAGENUM = 2;	//管理线程一次添加或删除的线程数
//
//public:
//	int getBusyThreads()
//	{
//		return m_numBusyThreads.load();
//	}
//
//public:
//	ThreadPool(int min, int max) :m_threadManagement(ThreadPool::threadManage, this), m_numMinThreads(min < 1 ? 1 : min), m_numMaxThreads(max)
//	{
//		m_shutdown = false;
//		m_numCurThreads = m_numMinThreads;	//从最小线程数开始
//		m_numBusyThreads = 0;
//		m_numExitThreads = 0;
//
//		for (int i = 0; i < m_numCurThreads; i++)
//		{
//			std::unique_lock<std::mutex> ulThreads(mtxThreads);
//			m_threads.emplace_back([this]() {
//				m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
//				threadTask();
//				});
//		}
//
//
//	}
//	ThreadPool(ThreadPool& another) = delete;	//禁用拷贝
//	ThreadPool& operator=(ThreadPool& another) = delete;	//禁用operator=
//	~ThreadPool()
//	{
//		//析构销毁线程池，释放资源
//		m_shutdown = true;	//线程池停止标志置true
//		cvTasksNotEmpty.notify_all();	//线程池要销毁了。通知所有线程全部不阻塞向下执行
//
//		for (auto& item : m_threads)	//不用加锁，访问m_threads的只有主线程和管理者线程，但因为shutdown=true，管理者线程已经不会访问了。
//		{
//			item.join();	//等待全部线程return终止
//		}
//
//		m_threadManagement.join();	//等待管理线程终止
//	}
//
//	//子线程任务
//	void threadTask()
//	{
//		while (true)
//		{
//			std::unique_lock<std::mutex> ulTasks(mtxTasks);
//			//任务队列非空或线程池关闭，拿到mtxTask向下执行
//			cvTasksNotEmpty.wait(ulTasks, [=]() {
//				return !m_tasks.empty() || m_shutdown;
//				});
//
//			//判断当前管理者线程是否要减少线程池中线程。这样销毁的线程要从m_threads中去掉。这些线程只能detach，因为没法在析构中join()。
//			//也可以再用个vector<std::thread>存储这些被管理者要销毁的线程，在析构时join()，但是麻烦。
//
//			if (m_numExitThreads > 0)
//			{
//				m_numExitThreads.fetch_sub(1, std::memory_order_relaxed);
//				if (m_numCurThreads > m_numMinThreads)
//				{
//					m_numCurThreads.fetch_sub(1, std::memory_order_relaxed);
//					//关闭当前线程
//					for (auto iter = m_threads.begin(); iter != m_threads.end();)
//					{
//						if (iter->get_id() == std::this_thread::get_id())
//						{
//							iter->detach();
//							std::unique_lock<std::mutex> ulThreads(mtxThreads);
//							iter = m_threads.erase(iter);
//						}
//						else
//						{
//							iter++;
//						}
//					}
//					return;
//				}
//
//			}
//
//			//判断是否线程池被关闭，管理者线程不工作。m_threads中线程数固定，在析构中全部都要join()，闲置线程直接return终止
//			if (m_shutdown == true && m_tasks.empty())
//			{
//				return;
//			}
//
//			//取任务执行
//			std::function<void()> task(std::move(m_tasks.front()));
//			m_tasks.pop();
//			std::cout << "threadID=" << std::this_thread::get_id() << ",start working...\n";
//			ulTasks.unlock();
//			m_numBusyThreads.fetch_add(1, std::memory_order_relaxed);
//
//			task();	//线程执行任务
//
//			m_numBusyThreads.fetch_sub(1, std::memory_order_relaxed);
//			std::cout << "threadID=" << std::this_thread::get_id() << ",end working...\n";	//线程执行完任务日志输出
//		}
//	}
//
//	////主线程添加任务。生产者
//	//template<typename F, typename... Args>
//	//auto addTask(F&& f, Args&&... args)	-> decltype(f)
//	//{
//	//	auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	//f和args是万能引用需要完美转发，通过bind把参数绑定到函数f上
//	//	//局部作用域，限定互斥锁ul锁定范围
//	//	{
//	//		std::unique_lock<std::mutex> ulTasks(mtxTasks);	//要访问共享变量m_tasks，上锁
//	//		m_tasks.emplace(std::move(task));		//任务队列里放1个任务，移动语义避免拷贝
//	//	}
//	//	cvTasksNotEmpty.notify_one();	//放了个任务，解除1个线程的阻塞向下执行任务
//	//}
//
	////让主线程知道子线程执行完了任务
	//template<typename F, typename... Args>
	//auto addTask(F&& f, Args&&... args)	-> std::future<decltype(f(args...)) >
	//{
	//	/*using fReturnType = decltype(f(args...));
	//	auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	
	//	std::packaged_task<fReturnType()> ptTask(task);
	//	std::future<fReturnType> res = ptTask.get_future();*/


	//	using return_type = typename std::result_of<F(Args...)>::type;
	//	auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	//	std::future<return_type> res = task->get_future();
	//	{
	//		std::unique_lock<std::mutex> lock(mtxTasks);
	//		if (m_shutdown) {
	//			throw std::runtime_error("addTask on stopped ThreadPool");
	//		}
	//		m_tasks.emplace([task]() { (*task)(); });
	//	}
	//	cvTasksNotEmpty.notify_one();	
	//	return res;
	//}
//
//
//	//管理者线程任务
//	static void threadManage(ThreadPool* poolInstance);
//
//};
//
//void ThreadPool::threadManage(ThreadPool* poolInstance)
//{
//	while (!poolInstance->m_shutdown)
//	{
//		std::this_thread::sleep_for(std::chrono::seconds(3));
//
//		//如果只是使用共享变量的值而不修改，可以用一个锁集中读取，然后使用。否则这些变量的读取放在代码中，分散开来，不方便上锁、解锁
//		std::unique_lock<std::mutex> ulTasks(poolInstance->mtxTasks);
//		int numTasks = static_cast<int>(poolInstance->m_tasks.size());
//		ulTasks.unlock();
//
//		//加线程
//		if (poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads && poolInstance->m_numCurThreads < numTasks)
//		{
//			for (int i = 0; i < poolInstance->THREADMANAGENUM && poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads; i++)
//			{
//				std::unique_lock<std::mutex> ulThreads(poolInstance->mtxThreads);
//				poolInstance->m_threads.emplace_back([poolInstance]() {
//					poolInstance->threadTask();
//					});
//			}
//			//写共享变量，只能这样加锁、解锁包起来
//			poolInstance->m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
//		}
//		//减少线程
//		if (poolInstance->m_numBusyThreads * 2 < poolInstance->m_numCurThreads && poolInstance->m_numCurThreads > poolInstance->m_numMinThreads)
//		{
//			poolInstance->m_numExitThreads.store(poolInstance->THREADMANAGENUM);
//
//			//通知m_numExitThreads个阻塞的线程向下执行，就会退出
//			for (int i = 0; i < poolInstance->m_numExitThreads; i++)
//			{
//				poolInstance->cvTasksNotEmpty.notify_one();
//			}
//		}
//
//	}
//}
//
//
//std::mutex mtxfunc;
//int data = 0;
//int func()
//{
//	for (int i = 0; i < 10; i++)
//	{
//		std::unique_lock<std::mutex> ul(mtxfunc);
//		data++;
//	}
//	return data;
//}
//
//int main()
//{
//	ThreadPool* tp = new ThreadPool(2, 10);
//	auto start1 = std::chrono::steady_clock::now();
//	std::future<int> res1 = tp->addTask(func);
//	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res1.get() << std::endl;
//
//
//
//
//
//	/*std::future<int> res2 = tp->addTask(func);
//	std::future<int> res3 = tp->addTask(func);
//	std::future<int> res4 = tp->addTask(func);
//	std::future<int> res5 = tp->addTask(func);
//	std::future<int> res6 = tp->addTask(func);
//
//	res1.wait();
//	res2.wait();
//	res3.wait();
//	res4.wait();
//	res5.wait();
//	res6.wait();*/
//
//
//	
//	/*auto status = res1.wait_for(std::chrono::microseconds(100));
//	if (status == std::future_status::ready)
//	{
//		std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res1.get() << std::endl;
//	}
//	else if (status == std::future_status::timeout)
//	{
//		std::cout << "timeout.." << std::endl;
//	}
//
//	auto end1 = std::chrono::steady_clock::now();
//	std::cout << "pool spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << "ms" << std::endl;*/
//
//
//
//
//	/*auto start2 = std::chrono::steady_clock::now();
//	for (int i = 0; i < 60000; i++)
//	{
//		data++;
//	}
//	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << data << std::endl;
//	auto end2 = std::chrono::steady_clock::now();
//	std::cout << "mainthread spend:" << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << "ms" << std::endl;*/
//
//	delete tp;
//}


#include <iostream> 
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <future>

class ThreadPool
{
private:
	std::queue<std::function<void()>> m_tasks;	//任务队列。bind绑定了参数，所以function的模版类型是void()
	std::vector<std::thread> m_threads;			//线程容器
	std::thread m_threadManagement;	//管理者线程
	//std::vector<std::thread> m_exitedThreads;	//暂存已退出线程池的线程

	std::condition_variable cvTasksNotEmpty;	//条件变量，任务队列非空获得锁
	std::mutex mtxTasks;
	std::mutex mtxThreads;
	std::mutex mtxPoolFields;

	bool m_shutdown;			//线程池关闭flag
	int m_numMinThreads;	//初始线程数
	int m_numMaxThreads;	//线程最大数
	std::atomic<int> m_numCurThreads;		//当前线程数
	std::atomic<int> m_numBusyThreads;	//当前正在工作的线程数
	std::atomic<int> m_numExitThreads;	//当前要销毁的线程数
	const int THREADMANAGENUM = 2;	//管理线程一次添加或删除的线程数

public:
	int getBusyThreads()
	{
		return m_numBusyThreads.load();
	}

public:
	ThreadPool(int min, int max) :m_threadManagement(ThreadPool::threadManage, this), m_numMinThreads(min < 1 ? 1 : min), m_numMaxThreads(max)
	{
		m_shutdown = false;
		m_numCurThreads = m_numMinThreads;	//从最小线程数开始
		m_numBusyThreads = 0;
		m_numExitThreads = 0;

		for (int i = 0; i < m_numCurThreads; i++)
		{
			std::unique_lock<std::mutex> ulThreads(mtxThreads);
			m_threads.emplace_back([this]() {
				m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
				threadTask();
				});
		}


	}
	ThreadPool(ThreadPool& another) = delete;	//禁用拷贝
	ThreadPool& operator=(ThreadPool& another) = delete;	//禁用operator=
	~ThreadPool()
	{
		//析构销毁线程池，释放资源
		m_shutdown = true;	//线程池停止标志置true
		cvTasksNotEmpty.notify_all();	//线程池要销毁了。通知所有线程全部不阻塞向下执行

		for (auto& item : m_threads)	//不用加锁，访问m_threads的只有主线程和管理者线程，但因为shutdown=true，管理者线程已经不会访问了。
		{
			item.join();	//等待全部线程return终止
		}

		m_threadManagement.join();	//等待管理线程终止
	}

	//子线程任务
	void threadTask()
	{
		while (true)
		{
			std::unique_lock<std::mutex> ulTasks(mtxTasks);
			//任务队列非空或线程池关闭，拿到mtxTask向下执行
			/*cvTasksNotEmpty.wait(ulTasks, [=]() {
				return !m_tasks.empty() || m_shutdown;
				});*/
			while (m_tasks.empty() && !m_shutdown)
			{
				cvTasksNotEmpty.wait(ulTasks);
			}

			//判断当前管理者线程是否要减少线程池中线程。这样销毁的线程要从m_threads中去掉。这些线程只能detach，因为没法在析构中join()。
			//也可以再用个vector<std::thread>存储这些被管理者要销毁的线程，在析构时join()，但是麻烦。

			if (m_numExitThreads > 0)
			{
				m_numExitThreads.fetch_sub(1, std::memory_order_relaxed);
				if (m_numCurThreads > m_numMinThreads)
				{
					m_numCurThreads.fetch_sub(1, std::memory_order_relaxed);
					//关闭当前线程
					for (auto iter = m_threads.begin(); iter != m_threads.end();)
					{
						if (iter->get_id() == std::this_thread::get_id())
						{
							iter->detach();
							std::unique_lock<std::mutex> ulThreads(mtxThreads);
							iter = m_threads.erase(iter);
						}
						else
						{
							iter++;
						}
					}
					return;
				}

			}

			//判断是否线程池被关闭，管理者线程不工作。m_threads中线程数固定，在析构中全部都要join()，闲置线程直接return终止
			if (m_shutdown == true && m_tasks.empty())
			{
				return;
			}

			//取任务执行
			std::function<void()> task(std::move(m_tasks.front()));
			m_tasks.pop();
			std::cout << "threadID=" << std::this_thread::get_id() << ",start working..." << std::endl;
			ulTasks.unlock();
			m_numBusyThreads.fetch_add(1, std::memory_order_relaxed);

			task();	//线程执行任务

			m_numBusyThreads.fetch_sub(1, std::memory_order_relaxed);
			std::cout << "threadID=" << std::this_thread::get_id() << ",end working..." << std::endl;	//线程执行完任务日志输出
		}
	}

	//主线程添加任务。生产者
	template<typename R, typename F, typename... Args>
	std::future<R> addTask(F&& f, Args&&... args)
	{
		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);	
		auto taskPtr = std::make_shared<std::packaged_task<R()>>(std::packaged_task<R()>(task));
		//auto task = std::make_shared<std::packaged_task<R()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

		//局部作用域，限定互斥锁ul锁定范围
		{
			std::unique_lock<std::mutex> ulTasks(mtxTasks);	//要访问共享变量m_tasks，上锁
			m_tasks.emplace([taskPtr]() {
				(*taskPtr)();
				});		//任务队列里放1个任务，移动语义避免拷贝
		}
		cvTasksNotEmpty.notify_one();	//放了个任务，解除1个线程的阻塞向下执行任务
		return taskPtr->get_future();
	}

	//管理者线程任务
	static void threadManage(ThreadPool* poolInstance);

};

void ThreadPool::threadManage(ThreadPool* poolInstance)
{
	while (!poolInstance->m_shutdown)
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));

		//如果只是使用共享变量的值而不修改，可以用一个锁集中读取，然后使用。否则这些变量的读取放在代码中，分散开来，不方便上锁、解锁
		std::unique_lock<std::mutex> ulTasks(poolInstance->mtxTasks);
		int numTasks = static_cast<int>(poolInstance->m_tasks.size());
		ulTasks.unlock();

		//加线程
		if (poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads && poolInstance->m_numCurThreads < numTasks)
		{
			for (int i = 0; i < poolInstance->THREADMANAGENUM && poolInstance->m_numCurThreads < poolInstance->m_numMaxThreads; i++)
			{
				std::unique_lock<std::mutex> ulThreads(poolInstance->mtxThreads);
				poolInstance->m_threads.emplace_back([poolInstance]() {
					poolInstance->threadTask();
					});
			}
			//写共享变量，只能这样加锁、解锁包起来
			poolInstance->m_numCurThreads.fetch_add(1, std::memory_order_relaxed);
		}
		//减少线程
		if (poolInstance->m_numBusyThreads * 2 < poolInstance->m_numCurThreads && poolInstance->m_numCurThreads > poolInstance->m_numMinThreads)
		{
			poolInstance->m_numExitThreads.store(poolInstance->THREADMANAGENUM);

			//通知m_numExitThreads个阻塞的线程向下执行，就会退出
			for (int i = 0; i < poolInstance->m_numExitThreads; i++)
			{
				poolInstance->cvTasksNotEmpty.notify_one();
			}
		}

	}
}


std::mutex mtxfunc;
int data = 0;
int func()
{
	for (int i = 0; i < 1000000; i++)
	{
		std::unique_lock<std::mutex> ul(mtxfunc);
		data++;
	}
	return data;
}

int main()
{
	ThreadPool* tp = new ThreadPool(5, 10);
	std::future<int>&& res1 = tp->addTask<int, int()>(func);
	std::future<int>&& res2 = tp->addTask<int, int()>(func);
	std::future<int>&& res3 = tp->addTask<int, int()>(func);
	std::future<int>&& res4 = tp->addTask<int, int()>(func);
	std::future<int>&& res5 = tp->addTask<int, int()>(func);

	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res1.get() << std::endl;
	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res2.get() << std::endl;
	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res3.get() << std::endl;
	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res4.get() << std::endl;
	std::cout << "MainThreadID=" << std::this_thread::get_id() << ", final data= " << res5.get() << std::endl;

	delete tp;

}