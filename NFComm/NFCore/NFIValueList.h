// -------------------------------------------------------------------------
//    @FileName         :    NFIValueList.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFIValueList
//
// -------------------------------------------------------------------------

#ifndef _NFI_VALUELIST_H_
#define _NFI_VALUELIST_H_

#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include <map>
#include <typeinfo>
#include <iomanip>
#include <functional>
#include <iostream>
#include <fstream>
#include <memory>
#include "NFIDENTID.h"
#include "NFPlatform.h"
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <boost/algorithm/string.hpp>

//变量类型
enum VARIANT_TYPE
{
    VTYPE_UNKNOWN,  // 未知
    VTYPE_INT,              // 32位整数
    VTYPE_FLOAT,            // 单精度浮点数
    VTYPE_DOUBLE,       // 双精度浮点数
    VTYPE_STRING,       // 字符串
    VTYPE_OBJECT,       // 对象ID
    VTYPE_POINTER,      // 指针
    VTYPE_MAX,
};

const static std::string NULL_STR = "";

//类型接口
class NFIValueList
{
public:
    struct VarData
    {
    public:
        VarData()
        {
            nType = VTYPE_UNKNOWN;
        }

        ~VarData()
        {
            nType = VTYPE_UNKNOWN;
        }

        VARIANT_TYPE nType;
        boost::variant<bool, int, float, double, std::string, NFINT64, void*> variantData;
    };

    virtual ~NFIValueList() = 0;

    virtual std::string StringValEx(const int index, const bool bForce) const = 0;
    virtual bool ToString(OUT std::string& str, const char* strSplit) = 0;

    template<typename NumberType>
    NumberType NumberVal(const int index) const
    {
        NumberType result = 0;
        if (index < mnSize && index >= 0)
        {
            VARIANT_TYPE type =  Type(index);
            if (type == VTYPE_DOUBLE
                || type == VTYPE_FLOAT
                || type == VTYPE_INT
                || type == VTYPE_OBJECT
                || type == VTYPE_POINTER)
            {
                const VarData* var = GetStackConst(index);
                result = boost::get<NumberType>(var->variantData);
            }
        }

        return result;
    }

    template<typename NumberType>
    bool SetNumber(const int index, const NumberType& value)
    {
        if (index < mnSize && index >= 0)
        {
            VARIANT_TYPE type =  Type(index);
            if (type == VTYPE_DOUBLE
                || type == VTYPE_FLOAT
                || type == VTYPE_INT
                || type == VTYPE_OBJECT
                || type == VTYPE_POINTER)
            {
                VarData* var = GetStack(index);
                var->variantData = value;
                return true;
            }
        }

        return false;
    }

    template<typename NumberType>
    bool AddNumber(const VARIANT_TYPE eType, const NumberType& value)
    {

        VarData* var = GetStack(mnSize);
        if (var)
        {
            var->nType = eType;
            var->variantData = value;
            mnSize++;

            return true;
        }

        return false;
    }

protected:
    //根据序号得到阶,8->16->32
    int GetOrder(const int index, int& nNewIndex) const
    {
        int nOrder = -1;
        int nLastStackSize = STACK_SIZE;
        nNewIndex = index;

        while (nNewIndex - nLastStackSize >= 0)
        {
            nOrder++;

            nNewIndex -= nLastStackSize;
            nLastStackSize *= 2;
        }

        return nOrder;
    }

    VarData* GetStack(const int index)
    {
        //mnNewSize是8的阶层
        if (index < STACK_SIZE)
        {
            return &mvStack[index];
        }
        else if (index < mnCapacity)
        {
            int nOrderIndex = 0;
            int nOrder = GetOrder(index, nOrderIndex);
            if (nOrder >= 0)
            {
                VarData* pData = mvList[nOrder];
                return &pData[nOrderIndex];
            }
        }
        else if (index == mnCapacity)
        {
            VarData* pData = new VarData[mnNextOrderCapacity];
            mvList.push_back(pData);
            mvList[mnOrder] = pData;
            mnOrder += 1;
            mnCapacity += mnNextOrderCapacity;
            mnNextOrderCapacity *= 2;

            return GetStack(index);
        }

        return NULL;
    }

public:
    const VarData* GetStackConst(const int index) const
    {
        //mnNewSize是8的阶层
        if (index < STACK_SIZE)
        {
            return &mvStack[index];
        }
        else if (index < mnCapacity)
        {
            int nOrderIndex = 0;
            int nOrder = GetOrder(index, nOrderIndex);
            if (nOrder >= 0)
            {
                VarData* pData = mvList[nOrder];
                return &pData[nOrderIndex];
            }
        }

        return NULL;
    }


    // 合并
    virtual bool Concat(const NFIValueList& src) = 0;
    // 部分添加
    virtual bool Append(const NFIValueList& src, int start, int count) = 0;
    // 部分添加
    virtual bool Append(const NFIValueList::VarData& svarData) = 0;
    // 清空
    virtual void Clear() = 0;
    // 是否为空
    virtual bool IsEmpty() const = 0;
    // 数据数量
    virtual int GetCount() const = 0;
    // 数据类型
    virtual VARIANT_TYPE Type(const int index) const = 0;
    //数据类型检测
    virtual bool TypeEx(const  int nType, ...) const = 0;
    //新进入拆分
    virtual bool Split(const char* str, const char* strSplit) = 0;

    // 添加数据
    virtual bool AddInt(const int value) = 0;
    virtual bool AddFloat(const float value) = 0;
    virtual bool AddDouble(const double value) = 0;
    virtual bool AddString(const char* value) = 0;
    virtual bool AddObject(const NFIDENTID& value) = 0;
    virtual bool AddPointer(const void* value) = 0;

    virtual bool SetInt(const int index, const int value) = 0;
    virtual bool SetFloat(const int index, const float value) = 0;
    virtual bool SetDouble(const int index, const double value) = 0;
    virtual bool SetString(const int index, const char* value) = 0;
    virtual bool SetObject(const int index, const NFIDENTID& value) = 0;
    virtual bool SetPointer(const int index, const void* value) = 0;

    // 获得数据
    virtual int IntVal(const int index) const = 0;
    virtual float FloatVal(const int index) const = 0;
    virtual double DoubleVal(const int index) const = 0;
    virtual const std::string& StringVal(const int index) const = 0;
    virtual NFIDENTID ObjectVal(const int index) const = 0;
    virtual void* PointerVal(const int index) const = 0;

    static bool Valid(const NFIValueList::VarData& var)
    {
        bool bChanged = false;

        switch (var.nType)
        {
        case VTYPE_INT:
            {
                if (0 != boost::get<int>(var.variantData))
                {
                    bChanged = true;
                }
            }
            break;
        case VTYPE_FLOAT:
            {
                float fValue = boost::get<float>(var.variantData);
                if (fValue > 0.001f  || fValue < -0.001f)
                {
                    bChanged = true;
                }
            }
            break;
        case VTYPE_DOUBLE:
            {
                float fValue = boost::get<float>(var.variantData);
                if (fValue > 0.001f  || fValue < -0.001f)
                {
                    bChanged = true;
                }
            }
            break;
        case VTYPE_STRING:
            {
                const std::string& strData = boost::get<const std::string&>(var.variantData);
                if (!strData.empty())
                {
                    bChanged = true;
                }
            }
            break;
        case VTYPE_OBJECT:
            {
                if (0 != boost::get<NFINT64>(var.variantData))
                {
                    bChanged = true;
                }
            }
            break;
        case VTYPE_POINTER:
            {
                if (0 != boost::get<void*>(var.variantData))
                {
                    bChanged = true;
                }
            }
            break;
        default:
            break;
        }

        return bChanged;
    }

    inline bool Compare(const int nPos, const NFIValueList& src) const
    {
        if (src.GetCount() > nPos
            && GetCount() > nPos
            && src.Type(nPos) == Type(nPos))
        {
            switch (src.Type(nPos))
            {
                case VTYPE_INT:
                    return IntVal(nPos) == src.IntVal(nPos);
                    break;

                case VTYPE_FLOAT:
                    return fabs(FloatVal(nPos) - src.FloatVal(nPos)) < 0.001f;
                    break;

                case VTYPE_DOUBLE:
                    return fabs(DoubleVal(nPos) - src.DoubleVal(nPos)) < 0.001f;
                    break;

                case VTYPE_STRING:
                    return StringVal(nPos) == src.StringVal(nPos);
                    break;

                case VTYPE_OBJECT:
                    return ObjectVal(nPos) == src.ObjectVal(nPos);
                    break;

                case VTYPE_POINTER:
                    return PointerVal(nPos) == src.PointerVal(nPos);
                    break;

                default:
                    return false;
                    break;
            }
        }

        return false;
    }

    inline bool operator==(const NFIValueList& src) const
    {
        if (src.GetCount() == GetCount())
        {
            for (int i = 0; i < GetCount(); i++)
            {
                if (!Compare(i, src))
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    inline bool operator!=(const NFIValueList& src)
    {
        return !(*this == src);
    }

    inline NFIValueList& operator<<(const char value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const unsigned char value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const short value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const unsigned short value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const int value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const unsigned int value)
    {
        AddInt(value);
        return *this;
    }
    inline NFIValueList& operator<<(const long value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const unsigned long value)
    {
        AddInt((int)value);
        return *this;
    }
    inline NFIValueList& operator<<(const float value)
    {
        AddFloat(value);
        return *this;
    }
    inline NFIValueList& operator<<(const double value)
    {
        AddDouble(value);
        return *this;
    }
    inline NFIValueList& operator<<(const char* value)
    {
        AddString(value);
        return *this;
    }
    inline NFIValueList& operator<<(const std::string& value)
    {
        AddString(value.c_str());
        return *this;
    }
    //     inline NFIValueList& operator<<( const NFINT64 value )
    //     {
    //         AddObject( NFIDENTID( value ) );
    //         return *this;
    //     }
    inline NFIValueList& operator<<(const NFIDENTID& value)
    {
        AddObject(value);
        return *this;
    }
    inline NFIValueList& operator<<(const void* value)
    {
        AddPointer(value);
        return *this;
    }
    inline NFIValueList& operator<<(const NFIValueList& value)
    {
        Concat(value);
        return *this;
    }
    enum { STACK_SIZE = 8 };
protected:
    int mnCapacity; //容量
    int mnSize;         //当前使用了的对象数量
    int mnNextOrderCapacity;
    NFINT16 mnOrder;            //扩充了几阶
    boost::array<VarData, STACK_SIZE> mvStack;
    std::vector<VarData*> mvList;
};

inline NFIValueList::~NFIValueList() {}

#endif
