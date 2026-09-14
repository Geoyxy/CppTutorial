#include <cstddef>
#include <cassert>
#include <stdexcept>

/**
* @brief 顺序表 
* @details 顺序存储结构，无扩容机制
* @tparam T 元素类型，必须支持==运算符
*/
template <typename T>
class SqList {
private:
	const std::size_t max_length_; ///< 顺序表的最大长度（容量）
	T* elements_ = nullptr;        ///< 指向顺序表的头元素
	std::size_t length_ = 0;       ///< 顺序表的当前长度
public:
	/**
	* @brief 构造长度为 max_length 的顺序表
	* @param max_length 顺序表的元素数量，默认值 100
	* @throw std::bad_alloc 如果分配内存失败
	*/
	explicit SqList(std::size_t max_length = 100);

	// 数据成员中存在资源，需要深拷贝
	/**
	* @brief 拷贝 list 构造顺序表
	* @param list 被拷贝的顺序表
	* @throw std::bad_alloc 如果分配内存失败
	*/
	SqList(const SqList& list);

	/** 
	* @brief 通过索引访问元素
	* @param 被访问元素的索引
	* @return 返回元素本身
	* @warning 不保证越界访问的安全性
	*/
	T& operator[](std::size_t pos);

	/**
	* @brief 通过索引访问元素
	* @param pos 被访问元素的索引
	* @return 返回元素本身
	* @warning 不保证越界访问的安全性
	*/
	const T& operator[](std::size_t pos) const;

	/**
	* @brief 通过索引访问元素
	* @param pos 被访问元素的索引
	* @return 返回元素本身
	* @throw std::out_of_range 当 pos >= length_
	*/
	T& At(std::size_t pos);

	/** 
	* @brief 根据元素对象查找，返回元素在顺序表中的索引
	* @param element 查找时对比的元素
	* @return 若找到，返回与 element 的值相同的元素的索引；否则返回 std::size_t(-1)
	*/
	std::size_t Find(const T& element);

	/**
	* @brief 在索引为pos的元素前插入element
	* @param pos 要插入的位置
	* @param element 要插入的元素
	* @throw std::runtime_error 当 length_ > max_length_ 时
	*/
	void Insert(std::size_t pos, const T& element);

	/**
	* @brief 删除索引为pos的元素
	* @param brief 要删除的元素的索引
	*/
	void Erase(std::size_t pos);

	// 遵守三法则
	/**
	* @warning 当 list.length_ > 本表的容量时会截断
	* @param list 被拷贝的顺序表 
	*/
	SqList& operator=(const SqList& list);

	// 实现RAII
	~SqList();
};

// ==================== 核心实现 ====================

template <typename T>
SqList<T>::SqList(std::size_t max_length)
	: max_length_(max_length),
	elements_(new T[max_length_]),
	length_(0) {}

template <typename T>
SqList<T>::SqList(const SqList& list)
	: max_length_(list.max_length_),
	elements_(new T[max_length_]),
	length_(list.length_) {
	for (std::size_t i = 0; i < length_; ++i) {
		this->elements_[i] = list[i];
	}
}

template <typename T>
T& SqList<T>::operator[](std::size_t pos) {
	assert(pos < length_); // 访问越界时报错
	return elements_[pos];
}

template <typename T>
const T& SqList<T>::operator[](std::size_t pos) const {
	assert(pos < length_); // 访问越界时报错
	return elements_[pos];
}

template <typename T>
T& SqList<T>::At(std::size_t pos) {
	// 检查是否越界
	if (pos >= length_) {
		throw std::out_of_range("访问越界");
	}
	return elements_[pos];
}

template <typename T>
std::size_t SqList<T>::Find(const T& element) {
	for (std::size_t i = 0; i < length_; ++i) {
		if (elements_[i] == element) return i;
	}
	return std::size_t(-1); // 返回一个size_t能表示的最大值
}

template <typename T>
void SqList<T>::Insert(std::size_t pos, const T& element) {
	// 索引越界时报错，这里允许索引取到length_处，以允许在尾部插入元素
	assert(pos <= length_);
	// 检查列表是否已满
	if (length_ >= max_length_) throw std::runtime_error("列表已满");
	// 将插入处及其以后的元素后移一位
	for (std::size_t i = length_; i > pos; --i) {
		elements_[i] = elements_[i - 1];
	}
	elements_[pos] = element;
	++length_;
}

template <typename T>
void SqList<T>::Erase(std::size_t pos) {
	assert(pos < length_); // 索引越界时报错
	// 将删除处及其以后的元素前移一位
	for (std::size_t i = pos; i < length_ - 1; ++i) {
		elements_[i] = elements_[i + 1];
	}
	--length_;
}

template <typename T>
SqList<T>& SqList<T>::operator=(const SqList& list) {
	// 检查是否为自赋值
	if (this == &list) return *this;
	// 确定拷贝范围
	size_t min_length = (list.length_ > this->max_length_ ? this->max_length_ : list.length_);

	for (std::size_t i = 0; i < min_length; ++i) {
		this->elements_[i] = list[i];
	}
	this->length_ = min_length;
	return *this;
}

template <typename T>
SqList<T>::~SqList() {
	delete[] elements_;
}

// ==================== 核心实现 ====================
