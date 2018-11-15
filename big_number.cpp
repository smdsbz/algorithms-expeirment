#include <iostream>
#include <stdexcept>
#include <string>
#include <list>


class BigNumber {

    std::string number;

private:

    static void _makeLengthEven(BigNumber &lhs, BigNumber &rhs, bool round = false) {
        if (!lhs.isPositive() || !rhs.isPositive()) {
            throw std::runtime_error(
                std::string("BigNumber::_makeLengthEven : ")
                + std::string("Operands must all be positive")
            );
        }
        int len_diff = lhs.getLengthDiffAgainst(rhs);
        if (len_diff < 0) {
            lhs.number = std::string(-len_diff, '0') + lhs.number;
        } else if (len_diff > 0) {
            rhs.number = std::string(len_diff, '0') + rhs.number;
        }
        if (round) {
            unsigned target_len = 1;
            while (target_len < lhs.number.size()) { target_len *= 2; }
            lhs.number = std::string(target_len - lhs.number.size(), '0') + lhs.number;
            rhs.number = std::string(target_len - rhs.number.size(), '0') + rhs.number;
        }
        return;
    }


    bool isLessThanAbs(const BigNumber &o) const {
        if (!(this->isPositive() && o.isPositive())) {
            throw std::runtime_error(
                std::string("Operands must all be positive")
            );
        }
        BigNumber lhs(*this), rhs(o);
        BigNumber::_makeLengthEven(lhs, rhs);
        for (unsigned idx = 0, range = lhs.number.size(); idx != range; ++idx) {
            if (lhs.number[idx] < rhs.number[idx]) {
                return true;
            }
            if (lhs.number[idx] > rhs.number[idx]) {
                return false;
            }
        }
        return false;
    }

public:

    BigNumber addPositiveValue(const BigNumber &o) const {
        if (!(this->isPositive() && o.isPositive())) {
            throw std::runtime_error(
                std::string("Operands must be positive numbers")
            );
        }
        // complement length, make even
        BigNumber lhs(*this), rhs(o);   // copies
        BigNumber::_makeLengthEven(lhs, rhs);
        // std::cout << lhs.str() << " + " << rhs.str() << std::endl;
        std::string result;
        int carry = 0;
        for (int idx = lhs.number.size() - 1; idx != -1; --idx) {
            int temp = (
                (lhs.number[idx] - '0')
                + (rhs.number[idx] - '0')
                + carry
            );
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result = std::to_string(temp) + result;
        }
        if (carry) {
            result = std::string("1") + result;
        }
        BigNumber retbn(result);
        return retbn;
    }


    BigNumber subtractPositiveNoLargerValue(const BigNumber &o) const {
        if ((*this) < o) {
            throw std::runtime_error(
                std::string("lhs smaller than rhs: ")
                + this->number + std::string(" and ") + o.number
            );
        }
        BigNumber lhs(*this), rhs(o);
        BigNumber::_makeLengthEven(lhs, rhs);
        int borrow = 0;
        std::string result;
        for (int idx = lhs.number.size() - 1; idx != -1; --idx) {
            int temp = (
                (lhs.number[idx] - '0')
                - (rhs.number[idx] - '0')
                - borrow
            );
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            } else {
                borrow = 0;
            }
            result = std::string(std::to_string(temp)) + result;
        }
        return BigNumber(result);
    }


    BigNumber &powerByTen(unsigned times) {
        this->number += std::string(times, '0');
        return *this;
    }


public:

    BigNumber() : number("0") { return; }

    ~BigNumber(void) { return; }

    BigNumber(const BigNumber &o) : number(o.number) { return; }

    BigNumber(const std::string &s) : number(s) {
        if (s.empty()) {
            throw std::runtime_error(std::string("Empty input value"));
        }
        if ((s[0] != '-') && (s[0] > '9' || s[0] < '0')) {
            throw std::runtime_error(std::string("Wrong input value: ") + s);
        }
        bool check = true;
        for (unsigned idx = 1, range = s.size(); idx != range; ++idx) {
            if (s[idx] > '9' || s[idx] < '0') {
                check = false;
                break;
            }
        }
        if (check) {
            this->number = s;
        } else {
            throw std::runtime_error(std::string("Wrong input value: ") + s);
        }
    }

    virtual std::string str(void) const {
        BigNumber temp(*this);
        temp.shrinkSpace();
        return temp.number;
    }

    virtual bool isPositive(void) const { return this->number[0] != '-'; }

    virtual unsigned len(void) const {
        if (this->isPositive()) {
            return this->number.size();
        }
        return this->number.size() - 1;
    }


    virtual void shrinkSpace(void) {
        bool is_neg = (this->number[0] == '-');
        if (is_neg) {
            this->number = this->number.substr(1);
        }
        auto first_not_zero = this->number.find_first_not_of('0');
        if (first_not_zero != std::string::npos) {
            this->number = this->number.substr(first_not_zero);
        }
        if (is_neg) {
            this->number = std::string("-") + this->number;
        }
    }


    virtual bool isCompatibleWith(const BigNumber &o) const {
        return this->len() == o.len();
    }


    virtual BigNumber getAbsoluteValue(void) const {
        BigNumber retbn;
        if (this->isPositive()) {
            retbn = BigNumber(*this);
        } else {
            retbn = BigNumber(this->number.substr(1));
        }
        return retbn;
    }


    virtual int getLengthDiffAgainst(const BigNumber &o) const {
        return this->len() - o.len();
    }


    virtual bool operator==(const BigNumber &o) const {
        BigNumber lhs(*this), rhs(o);
        lhs.shrinkSpace();
        rhs.shrinkSpace();
        return lhs.number == rhs.number;
    }

    virtual bool operator<(const BigNumber &o) const {
        bool lhs_neg = !this->isPositive(),
            rhs_neg = !o.isPositive();
        BigNumber lhs(this->getAbsoluteValue()), rhs(o.getAbsoluteValue());
        if (lhs_neg && rhs_neg) {
            return !lhs.isLessThanAbs(rhs);
        }
        if (lhs_neg && !rhs_neg) {
            return true;
        }
        if (!lhs_neg && rhs_neg) {
            return false;
        }
        return lhs.isLessThanAbs(rhs);
    }

    virtual bool operator>(const BigNumber &o) const {
        return ( !((*this) < o) && !((*this) == o) );
    }

    virtual bool operator<=(const BigNumber &o) const {
        return ( (*this) < o || (*this) == o );
    }

    virtual bool operator>=(const BigNumber &o) const {
        return ( !((*this) < o) );
    }

    virtual BigNumber operator-(void) const {
        BigNumber ret = *this;
        ret.number = std::string("-") + ret.number;
        return ret;
    }


    virtual BigNumber operator+(const BigNumber &o) const {
        bool
            is_lhs_pos = this->isPositive(),
            is_rhs_pos = o.isPositive();
        if (is_lhs_pos && is_rhs_pos) {     // if both positive
            return this->addPositiveValue(o);
        }
        if (!is_lhs_pos && !is_rhs_pos) {   // if both negative
            return -(
                this->getAbsoluteValue()
                .addPositiveValue(
                    o.getAbsoluteValue()
                )
            );
        }
        // one positive, one negative
        bool negate = false;
        BigNumber
            abs_lhs = this->getAbsoluteValue(),
            abs_rhs = o.getAbsoluteValue(),
            abs_dist;
        // get absolute distance
        if (abs_lhs > abs_rhs) {
            abs_dist = abs_lhs.subtractPositiveNoLargerValue(abs_rhs);
            if (!is_lhs_pos) {
                negate = true;
            }
        } else {
            abs_dist = abs_rhs.subtractPositiveNoLargerValue(abs_lhs);
            if (!is_rhs_pos) {
                negate = true;
            }
        }
        // return truth value
        if (negate) {
            return -abs_dist;
        }
        return abs_dist;
    }

    virtual BigNumber operator-(const BigNumber &o) const {
        return (*this) + (-o);
    }


    virtual BigNumber operator*(const BigNumber &o) const {
        // smallest case return
        if (this->len() == 2) {
            int rst = (
                std::stoi(this->number)
                * std::stoi(o.number)
            );
            return BigNumber(std::to_string(rst));
        }
        // get final result sign flag
        std::string sign_flag;
        if (this->isPositive() ^ o.isPositive()) {
            sign_flag = "-";
        }   // else omit '+' sign
        // make copy
        BigNumber lhs(this->getAbsoluteValue()), rhs(o.getAbsoluteValue());
        BigNumber::_makeLengthEven(lhs, rhs, true);
        // split
        unsigned split_idx = lhs.number.size() / 2;
        BigNumber lhs_high(lhs.number.substr(0, split_idx)),
            lhs_low(lhs.number.substr(split_idx)),
            rhs_high(rhs.number.substr(0, split_idx)),
            rhs_low(rhs.number.substr(split_idx));
        BigNumber temp_high(lhs_high * rhs_high),
            temp_low(lhs_low * rhs_low),
            temp_mid(
                (
                    (lhs_high.addPositiveValue(lhs_low))
                    .operator*(
                        rhs_high.addPositiveValue(rhs_low)
                    )
                ).subtractPositiveNoLargerValue(
                    temp_high.addPositiveValue(temp_low)
                )
            );
        BigNumber retbn(
            temp_high.powerByTen(lhs.number.size())
            .addPositiveValue(temp_mid.powerByTen(split_idx))
            .addPositiveValue(temp_low)
        );
        retbn.number = sign_flag + retbn.number;
        return retbn;
    }

};


int main(void) {

    BigNumber
        a(std::string("9223372036854775807")),
        b(std::string("1234567891111")),
        target(std::string("11386878964471969137416693151577"));
    BigNumber result = a * b;
    std::cout << a.str() << " * " << b.str() << " = "
              << result.str() << std::endl;
    std::cout << "Is equal to expected result? ";
    if (result == target) {
        std::cout << "Yes!" << std::endl;
    } else {
        std::cout << "Nein!" << std::endl;
    }

    std::cout << std::endl;

    a = target;
    target = BigNumber(std::string("1476434256335201019505915952536059041319"
        "057206399521214104693657122061789167297053187930937033"));
    result = a * a * a;
    std::cout << "ans * ans * ans = " << result.str() << std::endl;
    std::cout << "Is equal to expected result? ";
    if (result == target) {
        std::cout << "Yes!" << std::endl;
    } else {
        std::cout << "Nein!" << std::endl;
    }

    std::cout << std::endl;

    a = target; b = target;
    target = BigNumber(std::string("29528685126704020390118319050721180826381"
        "14412799042428209387314244123578334594106375861874066"));
    result = a + a;
    std::cout << "ans + ans = " << result.str() << std::endl;
    std::cout << "Is equal to expected result? ";
    if (result == target) {
        std::cout << "Yes!" << std::endl;
    } else {
        std::cout << "Nein!" << std::endl;
    }

    std::cout << std::endl;

    b = result;
    target = BigNumber(std::string("-1476434256335201019505915952536059041319"
        "057206399521214104693657122061789167297053187930937033"));
    result = a - b;
    std::cout << "ans - last_ans = " << result.str() << std::endl;
    std::cout << "Is equal to expected result? ";
    if (result == target) {
        std::cout << "Yes!" << std::endl;
    } else {
        std::cout << "Nein!" << std::endl;
    }

    return 0;
}
