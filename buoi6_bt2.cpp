#include<iostream>
#include <string>
#include<vector>
#include<memory>
//Hệ thống quản lý nhân viên
class Employee {
    protected:
    int id;
    std::string name;
    int age;
    double salary;

    public:
    Employee(int id, std::string name, int age, double salary)
        : id(id), name(std::move(name)), age(age), salary(salary) {}

    virtual void displayInfo() const {
        std::cout << "ID: " << id << ", Ten: " << name << ", Tuoi: " << age << ", Luong: " << salary << std::endl;
    } 

    virtual double getSalary() const {
        return salary;
    }

    void increaseSalary(double amount) {
        salary += amount;
    }

    virtual ~Employee() = default;
};

class Manager : public Employee {
    private:
    int teamSize;
    
    public:
    Manager(int id, std::string name, int age, double salary, int teamSize)
        : Employee(id, std::move(name), age, salary), teamSize(teamSize) {}

        void displayInfo() const override {
            Employee::displayInfo();
            std::cout << "So nhan vien quan ly: " << teamSize << std::endl;
        }

        double getSalary() const override {
            return Employee::getSalary() + (teamSize * 1000);
        }
};

class Company {
    private:
    std::vector<std::unique_ptr<Employee>> employees;

    public:
    void addEmployee(std::unique_ptr<Employee> emp) {
        employees.push_back(std::move(emp));
    }

    void displayAllEmployees() const {
        for (const auto& emp : employees) {
            emp->displayInfo();
            std::cout << "-------------------------" << std::endl;
        }
    }

    double getTotalSalary() const {
        double total = 0;
        for (const auto& emp : employees) {
            total += emp->getSalary();
        }
        return total;
    }
};

int main () {
    Company myCompany;
    myCompany.addEmployee(std::make_unique<Employee>(1, "Nguyen Van A", 30, 10000000));
    myCompany.addEmployee(std::make_unique<Employee>(2, "Tran Thi B", 25, 8000000));
    myCompany.addEmployee(std::make_unique<Manager>(3, "Le Van C", 40, 20000000, 5));

    std::cout << "Thong tin tat ca nhan vien:" << std::endl;
    myCompany.displayAllEmployees();

    std::cout << "Tong luong cong ty: " << myCompany.getTotalSalary() << std::endl;

    return 0;
}