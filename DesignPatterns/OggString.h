#if !defined(AFX_String_H__2CA5E3F6_86E2_4EA7_A56F_CE716B8B1E05__INCLUDED_)
#define AFX_String_H__2CA5E3F6_86E2_4EA7_A56F_CE716B8B1E05__INCLUDED_

#include "OggCore/OggDefs.h"

#include <vector>

namespace OGG {

////////////////////////////////////////////////////////////////////////

class Charset
{
public:
	enum Type
	{
		//! \brief Default编码
		// 在 Windows 平台上，为本地编码。具体编码需要通过 GetACP() 来获取。
		// 在 Linux 平台上，为本地编码。具体编码通过环境变量 LC_CTYPE 来获取。
		// 在 Android、IOS 平台上，为本地编码。即 UTF-8。
		Default = 1,
		//! \brief MAC编码
		MAC = 77,
		//! \brief ISO-2022-JP-2编码
		ISO2022JP2 = 127,
		//! \brief ShiftJIS编码
		ShiftJIS = 128,
		//! \brief Hangeul编码
		Hangeul = 129,
		//! \brief Johab编码
		Johab = 130,
		//! \brief GB18030编码
		GB18030 = 134,
		//! \brief GB2312编码
		GB2312 = 1340,
		//! \brief Big5繁体字符集
		ChineseBIG5 = 136,
		//! \brief Greek编码
		Greek = 161,
		//! \brief Turkish编码
		Turkish = 162,
		//! \brief Vietnamese编码
		Vietnamese = 163,
		//! \brief Hebrew编码
		Hebrew = 177,
		//! \brief Arabic编码
		Arabic = 178,
		//! \brief Baltic编码
		Baltic = 186,
		//! \brief Russian编码
		Russian = 204,
		//! \brief Thai编码
		Thai = 222,
		//! \brief EastEurope编码
		EastEurope = 238,
		//! \brief UTF8编码
		UTF8 = 250,
		//! \brief Windows默认的Unicode编码	
		UTF16LE = 251,
		//! \brief UCS2BE编码
		UTF16BE = 252,
		//! \brief Windows1252编码
		Windows1252 = 137,
		//! \brief Korean编码
		Korean = 131,
		//! \brief Cyrillic编码
		Cyrillic = 135,
		//! \brief UTF32编码
		UTF32LE = 8,
		//! \brief UTF32BE编码
		UTF32BE = 9
	};
};

////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////

typedef const CharT* MPCTSTR;

//! \brief 字符串类
//! \attention MBCString仅支持多字节编码的字符串。
class OGGCORE_API MBCString
{
public:
	//! \brief 默认构造函数。
	MBCString();

	//! \brief 拷贝构造函数。
	//! \param str 用来拷贝的字符串(MBCString类型)
	MBCString(const MBCString& str);

	//! \brief 拷贝构造函数
	//! \param str 用来拷贝的字符串(std::string类型)
	//! \remarks 主要用于和Markup等进行匹配
	MBCString(const std::string& str);

	//! \brief 拷贝构造函数。	
	//! \param pstr 用来拷贝的字符串(CharT*类型)
	MBCString(const CharT* pStr);

	//! \brief 拷贝构造函数。
	//! \param pstr 用来拷贝的字符串(CharT*类型)
	//! \param nSize 指定使用的字节长度
	MBCString(const CharT* pStr, int nSize);

	//! \brief 拷贝构造函数，将ch重复拷贝nRepeat次。
	//! \param ch 用来拷贝的字符串(CharT类型)
	//! \param nRepeat 重复拷贝次数,默认为1
	//! \remarks explicit用于防止隐形的转化
	explicit MBCString(CharT ch, int nRepeat = 1);

	//! \brief 追加字符串
	//! \param pch 要追加的字符串
	//! \param nSize 要追加的字节个数
	void Append(const CharT* pStr, int nSize);

	//! \brief 将MBCString转换为const char*。
	operator MPCTSTR() const;

	//! \brief 获取C字符串
	const CharT* Cstr() const;

	//! \brief 获取指定索引的字符。
	//! \param nIndex 指定的索引
	//! \return 返回指定索引的字符。
	CharT GetAt(int nIndex) const;

	//! \brief 设置指定索引的字符
	//! \param nIndex 指定的索引
	//! \param ch 要设置的字符
	void SetAt(int nIndex, CharT ch);

	//! \brief 获取指定索引的字符。
	//! \param nIndex 指定的索引
	//! \return 返回指定索引的字符
	CharT operator[](int nIndex) const;

	//! \brief 设置指定索引的字符的引用，支持str[i]='a';
	//! \param nIndex 指定的索引
	//! \return 返回指定索引的字符的引用
	CharT& operator[](int nIndex);

	//! \brief 保留指定字节个数的内存空间
	//! \param nCapacity 可容纳的字节个数
	//! \remarks 如果原有空间不够, 内存空间会增加。
	//! 如果原有空间比指定的大, 也不会释放空间。
	void SetCapacity(int nCapacity);

	//! \brief 获取目前所有空间(包括已经使用的和保留的)所占用的字节个数
	int GetCapacity() const;

	//! \brief 获取字符串长度
	int GetLength() const;

	//! \brief 设置字符串长度
	//! \param nLength 字节个数
	//! \remarks 如果长度变小,会自动截断; 
	//! 如果长度变大,会填充0x00。
	void SetLength(int nLength);

	//! \brief 把字符串内容转换为大写，不会修改非ASCII字符
	//! \return 返回自身的引用,支持连写
	MBCString& MakeUpper();

	//! \brief 把字符串内容转换为小写，不会修改非ASCII字符
	//! \return 返回自身的引用,支持连写
	MBCString& MakeLower();

	//! \brief 把字符串逆转
	//! \return 返回自身的引用,支持连写
	//! \remarks 支持中间带有中文（MBCS）的转换
	MBCString& MakeReverse();

	//! \brief 取出字符串对象左边的指定长度的子字符串
	//! \param nCount 字节个数
	//! \return 返回左边指定长度的子字符串
	MBCString Left(int nCount) const;

	//! \brief 取出字符串对象最右边的指定长度的子字符串
	//! \param nCount 字节个数
	//! \return 返回右边指定长度的子字符串
	MBCString Right(int nCount) const;

	//! \brief 从字符串对象中取出从指定索引起的子字符串对象
	//! \param nFirst 指定的中间的索引序号
	//! \return 返回从中间指定的索引开始,到最后的子字符串
	MBCString Mid(int nFirst) const;

	//! \brief 从字符串对象中获取从指定索引起、指定长度的子字符串对象
	//! \param nFirst nFirst 索引值，大于等于零
	//! \param nCount 要取出的字节个数
	MBCString Mid(int nFirst, int nCount) const;

	//! \brief 删除从指定索引起的指定长度的字符串
	//! \param nIndex 开始删除的索引值
	//! \param nCount 要删除的字节个数
	//! \return 返回删除字符串后的结果字符串对象的长度
	int Delete(int nIndex, int nCount = 1);

	//! \brief 在指定的索引之前插入字符串
	//! \param nIndex 指定的索引
	//! \param pstr 要插入的字符串
	//! \return 插入后,结果字符串的长度
	int Insert(int nIndex, const CharT* pStr);

	//! \brief 在指定的索引之前插入若干数目的字符
	//! \param nIndex 指定的索引
	//! \param ch 指定的字符
	//! \param nCount 字符重复的次数
	//! \return 插入后,结果字符串的长度
	int Insert(int nIndex, CharT ch, int nCount = 1);

	//! \brief 删除字符串对象中等于指定字符的字符
	//! \param ch 要删除的字符
	//! \return 返回删除的字符个数
	int Remove(CharT ch);

	//! \brief 删除字符串对象左边的空格（\\t\\r\\n）
	//! \return 删除后,字符串对象的引用
	MBCString& TrimLeft();

	//! \brief 删除字符串对象左边的指定字符
	//! \param ch 要删除的字符
	//! \return 删除后,字符串对象的引用
	MBCString& TrimLeft(CharT ch);

	//! \brief 删除字符串对象左边属于指定字符集合的字符
	//! \param pstr 指定的字符串集合
	//! \return 删除后,字符串对象的引用,以支持连写
	//! \remarks 对于字符集合,是要删除左边的存在于字符集合中的每一个字符
	MBCString& TrimLeft(const CharT* pStr);

	//! \brief 删除字符串对象右边的空格（\\t\\r\\n）
	//! \return 删除后,字符串对象的引用
	MBCString& TrimRight();

	//! \brief 删除字符串对象右边的指定字符
	//! \param ch 指定的字符
	//! \return 删除后,字符串对象的引用
	MBCString& TrimRight(CharT ch);

	//! \brief 删除字符串对象右边属于指定字符集合的字符
	//! \param pstr 指定的字符串集合
	//! \return 删除后,字符串对象的引用,以支持连写
	//! \remarks 对于字符集合,是要删除右边的存在于字符集合中的每一个字符
	MBCString& TrimRight(const CharT* pStr);

	//! \brief 删除字符串对象右边等于指定字符串的字符
	//! \param &str 指定的字符串
	//! \return 删除后,字符串对象的引用,以支持连写
	MBCString& TrimRightString(const MBCString& str);

	//! \brief 删除字符串对象左边等于指定字符串的字符
	//! \param &str 指定的字符串
	//! \return 删除后,字符串对象的引用,以支持连写
	MBCString& TrimLeftString(const MBCString& str);

	//! \brief 去除传入字符串中的逗号
	void RemoveComma();

	//! \brief 判断字符串是否为空
	//! \return 为空,返回true;不为空,返回false
	uBool IsEmpty() const;

	//! \brief 清空字符串
	void Empty();

	//! \brief 比较两个字符串的大小
	//! \param lpsz 要比较的字符串指针
	//! \return 小于返回负数；等于返回0；大于返回正数
	//! \remarks 区分大小写，按照内部值依顺序比较
	int Compare(const CharT* pStr) const;

	//! \brief 比较两个字符串的大小
	//! \param lpsz 要比较的字符串指针
	//! \return 小于返回负数；等于返回0；大于返回正数
	//! \remarks 不区分大小写，按照内部值依顺序比较
	int CompareNoCase(const CharT* pStr) const;

	//! \brief 比较两个字符串的大小
	//! \remarks 不区分大小写，按照内部值依顺序比较
	//! \param str 要比较的字符串
	//! \return 小于返回负数；等于返回0；大于返回正数。
	int CompareNoCase(const MBCString& str) const;

	//! \brief 从指定位置开始，查找指定的字符
	//!	\param ch 要查找的字符[in]。
	//!	\param nStart 查找起始位置，对应的字符会被查找[in]。
	//!	\return 返回找到的字符的索引值，从0算起。找不到返回-1
	int Find(CharT ch, int nStart = 0) const;

	//! \brief 从指定位置开始，查找完全相等的子字符串
	//!	\param lpszSub 要查找的子字符串[in]。
	//!	\param nStart 查找起始位置，对应的子字符串会被查找[in]。
	//!	\return 返回找到的子字符串的索引值，从0算起。找不到返回-1
	int Find(const CharT* pStrSub, int nStart = 0) const;

	//! \brief 从后向前查找指定的字符
	//!	\param ch 要查找的字符[in]。
	//!	\return 返回找到的字符的索引值，从0算起;找不到返回-1
	int ReverseFind(CharT ch) const;

	//! \brief 查找第一个“既在字符串对象中，又在指定的字符集合中”的字符的位置。
	//!	\param lpszCharSet 指定的字符集合[in]。
	//!	\return 返回找到的字符的索引，从0算起。找不到返回-1
	int FindOneOf(const CharT* pStrCharSet) const;

	//! \brief 得到字符串对象中，从第0个字符起，到不符合指定字符集合中的字符为止的子字符串。
	//! \param lpszCharSet 指定的字符集合[in]。
	//!	\return 返回符合条件的子字符串。
	MBCString SpanIncluding(const CharT* pStrCharSet) const;

	//! \brief 得到字符串对象中，从第0个字符起，到符合指定字符集合中的字符为止的子字符串。
	//! \param lpszCharSet 指定的字符集合[in]。
	//!	\return 返回符合条件的子字符串。
	MBCString SpanExcluding(const CharT* pStrCharSet) const;

	//! \brief 替换函数，把字符串对象中指定的字符替换为新的字符。
	//! \param chOld 指定要被替换的字符[in]。
	//!	\param chNew 新的字符[in]。
	//!	\return 返回替换的次数。
	//! \remarks 比较时区分大小写。
	int Replace(CharT chOld, CharT chNew);

	//! \brief 替换函数，把字符串对象中指定的子字符串替换为新的字符串
	//! \param lpszOld 指定要被替换的子字符串[in]。
	//!	\param lpszNew 新的字符串[in]。
	//!	\return 返回替换的次数。
	//!	\remarks 比较时区分大小写。
	int Replace(const CharT* pStrOld, const CharT* pStrNew);

	//! \brief 格式化函数，类似于sprintf。
	//!	\param fmt 用来表达格式的字符串[in]。
	//!	\param ... 可选参数[in]。
	//!	\remarks 不能将MBCString作为参数传进该函数，而必须调用MBCString的Cstr函数得到C字符串。
	//!			 不能将iLong、uLong等64位整数作为参数传入该函数,而应该先强制转化为32位整数
	void Format(const CharT* pStr, ...);


	//! \brief 字符串赋值函数。
	const MBCString& operator=(const MBCString& str);

	//! \brief 用std::string来赋值函数。
	//! \param str std::string类型的字符串,主要用于和Markup等进行匹配
	const MBCString& operator=(const std::string& str);

	//! \brief 用C 字符串赋值函数。	
	//! \param pstr C字符串参数
	const MBCString& operator=(const CharT* pStr);
	//! \brief 重载 +
	MBCString operator+(const CharT ch) const;
	//! \brief 重载 +
	MBCString operator+(const CharT* pStr) const;
	//! \brief 重载 +
	MBCString operator+(const MBCString& str) const;

	//! \brief 重载 +=
	const MBCString& operator+=(const MBCString& str);
	//! \brief 重载 +=
	const MBCString& operator+=(const CharT ch);
	//! \brief 重载 +=
	const MBCString& operator+=(const CharT* pStr);

	//! \brief 重载 ==
	bool operator==(const CharT* pStr) const;
	//! \brief 重载 ==
	bool operator==(const MBCString& str) const;

	//! \brief 重载 !=
	bool operator!=(const CharT* pStr) const;
	//! \brief 重载 !=
	bool operator!=(const MBCString& str) const;

	//! \brief 重载 <
	bool operator<(const MBCString& str) const;

	//! \brief 重载 +
	friend OGGCORE_API MBCString operator+(CharT ch, const MBCString& str);
	//! \brief 重载 +
	friend OGGCORE_API MBCString operator+(const CharT* pStr, const MBCString& str);

	//! \brief 把iLong型的数据转化为MBCString型字符串
	//! \param lVal 要转化的iLong型数据
	//! \param base 进制,默认为10进制,还支持16进制;其它暂时不支持
	//! \return 返回转化后的字符串
	//! \remarks 当base为16进制时,转化后的结果前面会加0X,字母都为大写。
	//! 用这种方式间接支持long型数据的Format,即先转化为MBCString,再用%s进行格式化。
	//! 采用静态函数，返回MBCString的方式，以便于调用的代码连写。
	static MBCString From(iLong lVal, uInt base = 10);
	//! \brief 把uLong型的数据转化为MBCString型字符串
	static MBCString From(uLong lVal, uInt base = 10);
	//! \brief 把int型的数据转化为MBCString型字符串
	static MBCString From(int nVal, uInt base = 10);
	//! \brief 把uInt型的数据转化为MBCString型字符串
	static MBCString From(uInt nVal, uInt base = 10);

	//Convert string to a integer number, assuming given number base
	//! \brief 把字符串转换为int型数值
	int ToInt(uInt base = 10) const;

	//! \brief 把字符串转换为无符号uInt型数值
	uInt ToUInt(uInt base = 10) const;

	//! \brief 把字符串转换为iLong型数值
	//! \param s 要转化的字符串
	//! \param base 进制,默认为10进制,还支持16进制;其它暂时不支持
	iLong ToLong(uInt base = 10) const;

	//! \brief 把字符串转换为无符号uLong型数值
	//! \param s 要转化的字符串
	//! \param base 进制,默认为10进制,还支持16进制;其它暂时不支持
	uLong ToULong(uInt base = 10) const;

	//Convert string into real number
	//! \brief 把字符串转换为float型数值
	float ToFloat() const;

	//! \brief 把字符串转换为double型数值	
	double ToDouble() const;

	//! \brief 把字符串按照指定的分隔符分割为一个字符串数组。
	//! \param dest 生成的字符串数组[out]。
	//!	\param delims 指定的分隔符，默认为回车换行[in]。
	//!	\param bKeepEmptyString 是否保留分割后 空的字符串, 如字符串";"通过';'分割后,dest数组的size
	//! 在保留空字符串的时候为2, 不保留的时候为0; 
	//!	\return 分割后字符串数组的长度。
	int Split(std::vector<MBCString>& strDests, const MBCString& strDelims = "\r\n", uBool bKeepEmptyString = false) const;

	//! \brief 设置字符串里面的字符的字符集
	void SetCharset(Charset::Type nCharset);
	//! \brief 获取字符串里面的字符的字符集
	Charset::Type GetCharset() const;

public:
	//! \brief 判断字符是否属于空ASCII字符, 包括：空格,\\t\\r\\n等
	static uBool IsSpacCharT(CharT ch);

	//! \brief 判断字符是否属于数字字符, 从 '0' 到 '9'
	static uBool IsDigit(CharT ch);

	//! \brief 判断字符是否属于十六进制字符, 包括从 '0' 到 '9', 'A'到'F', 'a'到'f'
	static uBool IsHexDigit(CharT ch);

	//! \brief 判断字符是否属于大写字符, 从 'A' 到 'Z'
	static uBool IsBigLetter(CharT ch);

	//! \brief 判断字符是否属于小写字符, 从 'a' 到 'z'
	static uBool IsLittleLetter(CharT ch);

	//! \brief 判断该字节是否是lead byte，即该字节和后续字节联合在一起构成一个双字节的字符（如中文、日文等）
	static uBool IsLeadByte(CharT ch);

	//! \brief 判断一个UCS2的字符是否是英文字符
	//! \return 如果是中文或日文等字符，返回false；是英文字符，返回true
	static uBool IsAscii(uShort ch);

	//! \brief 转成本地编码
	static MBCString ToLocal(const MBCString& src);

	//! \brief 转成全局编码
	static MBCString ToGlobal(const MBCString& src);

protected:
	//! \brief std的字符串
	std::string m_string;
	//! \brief 字符集
	int m_nCharset;

};

//! \brief 重载 ==
inline OGGCORE_API bool operator==(const CharT* pStr, const MBCString& str)
{
	return str == pStr;
}

typedef MBCString String;
typedef std::vector<String> Strings;

OGGCORE_API String translateTr(const CharT* context, const CharT* source);

////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

class OGGCORE_API UTF8String
{
public:
	UTF8String();
	UTF8String(const String& str, Charset::Type nTarget = Charset::Default);

	String ToString(Charset::Type nTarget = Charset::Default) const;
	void SetUTF8Char(const CharT* pStr);
	int GetLength() const;
	const CharT* Cstr() const;

protected:
	std::string m_string;

};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

class WString;
typedef const CharW* EPCTSTRW;
typedef std::vector<WString> WStrings;

class OGGCORE_API WString
{
public:
	WString();
	WString(const String& str);
	WString(const WString& str);
	WString(const CharW* str);
	WString(const CharW* str, const int nSize);
	WString(const std::wstring& str);
	~WString();
	operator EPCTSTRW() const;

	String ToString(Charset::Type enTarget = Charset::Default);
	void FromString(const String& str, Charset::Type enSource = Charset::Default);

	bool operator==(const CharW* pch) const;
	bool operator!=(const CharW* pch) const;

	const CharW* Cstr()const;

	CharW GetAt(int nIndex)const;
	void SetAt(int nIndex, CharW wch);
	CharW operator[](int nIndex)const;
	CharW& operator[](int nIndex);

	void SetCapacity(int nCapacity);
	int GetCapacity()const;
	const CharW* GetData()const;
	int GetLength()const;
	void MakeUpper();
	void MakeLower();
	void MakeInverse();

	WString Left(int nCount)const;
	WString Right(int nCount)const;
	WString Mid(int nFirst)const;
	WString Mid(int nFirst, int nCount)const;

	int Delete(int nIndex, int nCount = 1);
	int Insert(int nIndex, CharW* pstr);
	int Insert(int nIndex, CharW ch, int nCount = 1);
	int Remove(CharW ch);

	WString& TrimLeft();
	WString& TrimLeft(CharW ch);
	WString& TrimLeft(const CharW* pstr);
	WString& TrimRight();
	WString& TrimRight(CharW ch);
	WString& TrimRight(const CharW* pstr);

	uBool IsEmpty()const;
	void Empty();

	int Compare(const CharW* pstr)const;
	int CompareNoCase(const CharW* pstr)const;

	int Find(CharW ch) const;
	int ReverseFind(CharW ch) const;
	int Find(CharW ch, int nStart) const;
	int FindOneOf(const CharW* lpszCharSet) const;
	int Find(const CharW* lpszSub) const;
	int Find(const CharW* lpszSub, int nStart) const;

	WString SpanIncluding(const CharW* lpszCharSet) const;
	WString SpanExcluding(const CharW* lpszCharSet) const;

	int Replace(CharW chOld, CharW chNew);
	int Replace(const CharW* lpszOld, const CharW* lpszNew);

	int Split(WStrings& dest, const WString& delims = L"\r\n") const;

protected:
	std::wstring m_string;

};

//////////////////////////////////////////////////////////////////////////

}

#endif // !defined(AFX_String_H__2CA5E3F6_86E2_4EA7_A56F_CE716B8B1E05__INCLUDED_)
