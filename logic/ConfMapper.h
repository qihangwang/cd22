#pragma once

#include <string>

#include <Conf.h>

namespace ros { namespace pike { namespace logic {

// ������ ��������
class ConfMapper
{
public:
    // ��������� ��������� �� json-�����
    static Conf Load(const std::string& filename);
};

}}}
