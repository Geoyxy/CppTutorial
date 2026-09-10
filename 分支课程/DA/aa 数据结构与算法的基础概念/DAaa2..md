```
ADT List {
	数据对象：D = { aᵢ | aᵢ ∈ ElemSet, i = 1, 2, …, n, n ≥ 0 }
	数据关系：R = { ⟨aᵢ₋₁, aᵢ⟩ | aᵢ₋₁, aᵢ ∈ D, i = 2, …, n }
	基本操作：
		List()
			操作结果：构造一个空的线性表。
		~List()
			操作结果：销毁线性表
		ClearList()
			操作结果：清空线性表
		IsListEmpty()
			操作结果：若线性表为空，则返回 true，否则返回 false
		GetListLength()
			操作结果：获取线性表中的元素个数
		GetElem(i)
			初始条件：1 \le i \le GetListLength()
			操作结果：返回第 i 个数据元素的值
		operator[](i)
			初始条件：1 \le i \le GetListLength()
			操作结果：返回第 i 个数据元素的值
} ADT List
```

ADT List {
	数据对象: D={a_i|a_i \in ElemSet, i=1, 2, \dots, n, n\ge0}
}

```cpp
template <typename T>
T Find(int content) { ... }
```