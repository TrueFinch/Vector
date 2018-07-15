//
// Created by nixtaxe on 13.07.18.
//
#define CATCH_CONFIG_MAIN

#include <vector>
#include <exception>

#include "catch.h"
#include "vector.hpp"

TEST_CASE("STL compatibility", "[]") {
  SECTION ("Compare functions") {
    std::vector<int> expected1 = {1, 2, 3};
    std::vector<int> expected2 = {1, 2, 3, 4};
    tftl::vector<int> result1 = {1, 2, 3};
    tftl::vector<int> result2 = {1, 2, 3, 4};
    REQUIRE((expected1 < expected2) == (result1 < result2));
  }

  SECTION("iterator") {
    int arr[] = {1, 2, 3};
    tftl::iterator<int> it(arr);
    REQUIRE(it[0] == 1);
    std::advance(it, 1);
    REQUIRE(it[0] == 2);
    tftl::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> result(expected.begin(), expected.end());
    REQUIRE(expected == result);
  }

  SECTION("std::sort") {
    std::vector<int> expected = {0, 1, 2, 3, 4, 5};
    tftl::vector<int> result = {5, 3, 2, 4, 1, 0};
    std::sort(result.begin(), result.end());
    REQUIRE(result == expected);
  }

}

TEST_CASE("Constructing vector") {

  SECTION("Pass no arguments") {
    tftl::vector<int> result;
    tftl::vector<int>::size_type expectedCapacity = 0;
    REQUIRE(result.capacity() == expectedCapacity);
    REQUIRE(result.empty());
  }

  SECTION("Pass size") {
    tftl::vector<int>::size_type expectedSize = 4;
    tftl::vector<int> result(expectedSize);
    REQUIRE(result.size() == expectedSize);
    REQUIRE(result.capacity() >= expectedSize);
  }

  SECTION("Pass size and value for filling vector") {
    std::vector<int>::size_type expectedSize = 4;
    std::vector<int>::value_type expectedValue = 4;
    std::vector<int> expected(expectedSize, expectedValue);
    tftl::vector<int> result(expectedSize, expectedValue);
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Pass two iterators") {
    std::vector<int> expected{1, 2, 3, 4};
    tftl::vector<int> result(expected.begin(), expected.end());
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Pass initializer list") {
    std::vector<int> expected{1, 2, 3, 4};
    tftl::vector<int> result{1, 2, 3, 4};
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Pass rvalue reference") {
    std::vector<int> expected(std::vector<int>{1, 2, 3, 4});
    tftl::vector<int> result(tftl::vector<int>{1, 2, 3, 4});
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

}

TEST_CASE("Data info access") {

  SECTION("At access") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    REQUIRE(result.at(2) == expected.at(2));
  }

  SECTION("Front and back access") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    REQUIRE(result.front() == expected.front());
    REQUIRE(result.back() == expected.back());
  }

  SECTION("Data access") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    REQUIRE(*(result.data()) == *(expected.data()));
  }

  SECTION("vector size") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    REQUIRE(result.max_size() == expected.max_size());
  }

  SECTION("Allocator access") {
    tftl::vector<int> result = {1, 2, 3, 4};
    typename tftl::vector<int>::allocator_type a = result.get_allocator();
    REQUIRE(a == result.get_allocator());
    REQUIRE_FALSE(a != result.get_allocator());
  }

}

TEST_CASE("Vectors copy operator") {

  SECTION("Assign vector to initializer list") {
    std::vector<int> expected;
    expected = {1, 2, 3, 4};
    tftl::vector<int> result;
    result = {1, 2, 3, 4};
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Assign vector to vector") {
    tftl::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result;
    result = expected;
    REQUIRE(result == expected);
  }

  SECTION("Move assign vector to vector") {
    tftl::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> moveable = {1, 2, 3, 4};
    tftl::vector<int> result;
    result = std::move(moveable);
    REQUIRE(result == expected);
    REQUIRE(moveable.empty());
  }

  SECTION("Assign vector to the same vector") {
    tftl::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    result = result;
    result = std::move(result);
    REQUIRE(result == expected);
  }

}

TEST_CASE("Vector resizing") {

  SECTION("Pass size") {
    std::vector<int> expected = {1, 2, 3, 4};
    expected.resize(3);
    tftl::vector<int> result = {1, 2, 3, 4};
    result.resize(3);
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Pass size and default value for added elements") {
    std::vector<int> expected = {1, 2, 3, 4};
    expected.resize(6, 1);
    tftl::vector<int> result = {1, 2, 3, 4};
    result.resize(6, 1);
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }
}

TEST_CASE("Vector preallocation") {

  SECTION("Pass integer") {
    std::vector<int> expected = {1, 2, 3, 4};
    expected.reserve(20);
    tftl::vector<int> result = {1, 2, 3, 4};
    result.reserve(20);
    REQUIRE(result.capacity() >= expected.capacity());
    REQUIRE(result == expected);
  }

}

TEST_CASE("Vector modifications") {

  SECTION("Assign function passing size and value") {
    std::vector<int> expected;
    expected.assign(5, 1);
    tftl::vector<int> result;
    result.assign(5, 1);
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Assign function passing initializer list") {
    std::vector<int> expected;
    expected.assign({1, 2, 3, 4});
    tftl::vector<int> result;
    result.assign({1, 2, 3, 4});
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Assign funtion passing two iterators") {
    tftl::vector<int> expected{1, 2, 3, 4, 5};
    tftl::vector<int> result;
    result.assign(expected.begin(), expected.end());
    REQUIRE(result.capacity() >= expected.size());
    REQUIRE(result == expected);
  }

  SECTION("Push items back") {
    tftl::vector<int> expected = {9, 6, 44, 52, 1};
    tftl::vector<int> result;
    for (tftl::vector<int>::iterator it = expected.begin(); it != expected.end(); ++it) {
      result.push_back(*it);
    }
    REQUIRE(result == expected);
  }

  SECTION("Move push items back") {
    tftl::vector<int> expected = {9, 6, 44, 52, 1};
    tftl::vector<int> result;
    for (tftl::vector<int>::iterator it = expected.begin(); it != expected.end(); ++it) {
      result.push_back(std::move(*it));
    }
    REQUIRE(result.size() == expected.size());
  }

  SECTION("Pop items") {
    std::vector<int> expected = {1};
    tftl::vector<int> result = {1, 2, 3, 4};
    for (int i = 0; i < 3; ++i) {
      result.pop_back();
    }
    REQUIRE(result == expected);
  }

  SECTION("Insert one item") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 3, 4};
    result.insert(result.begin() + 1, 2);
    REQUIRE(result == expected);
  }

  SECTION("Insert same items several times") {
    tftl::vector<int> expected = {1, 2, 3, 3, 3, 4};
    tftl::vector<int> result = {1, 2, 4};
    result.insert(result.begin() + 2, 3, 3);
    REQUIRE(result == expected);
  }

  SECTION("Insert iterator range") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> resourse = {2, 3, 4};
    tftl::vector<int> result = {1};
    result.insert(result.begin() + 1, resourse.begin(), resourse.end());
    REQUIRE(result == expected);
  }

  SECTION("Insert initializer list") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1};
    result.insert(result.begin() + 1, {2, 3, 4});
    REQUIRE(result == expected);
  }

  SECTION("Erase one element") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 3, 4};
    result.erase(result.begin() + 2);
    REQUIRE(result == expected);
  }

  SECTION("Erase elements") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 3, 3, 3, 4};
    result.erase(result.begin() + 2, result.begin() + 5);
    REQUIRE(result == expected);
  }

  SECTION("Swap vectors") {
    tftl::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> forSwap = {1, 2, 3, 4};
    tftl::vector<int> result = {4, 3, 2, 1};
    result.swap(forSwap);
    REQUIRE(result == expected);
    expected = forSwap;
    std::swap(result, forSwap);
    REQUIRE(result == expected);
  }

  SECTION("Clear vector") {
    tftl::vector<int> result = {1, 2, 3, 4, 5};
    result.clear();
    REQUIRE(result.capacity() == 0);
    REQUIRE(result.empty());
  }

  SECTION("Shrink vector") {
    tftl::vector<int> result = {1, 2, 3, 4, 5, 6};
    result.shrink_to_fit();
    REQUIRE(result.capacity() == result.size());
  }
  SECTION("Emplace item back") {
    tftl::vector<int>::value_type expected = 4;
    tftl::vector<int> result;
    result.emplace_back(4);
    REQUIRE(result.front() == expected);
  }

  SECTION("Emplace item at positiion") {
    tftl::vector<int>::value_type expected = 4;
    tftl::vector<int> result(1);
    tftl::vector<int>::value_type a = *(result.emplace(result.begin() + 1, 4));
    REQUIRE(a == expected);
  }
}

TEST_CASE("Vector exceptions") {

  struct Error {
    const int a = 1;

    Error& operator=(const Error&) {
      throw std::exception();
    }
  };

  struct SomeType {
    int a = 4;

    SomeType(int a)
        : a(a) {
    }

    static void initVectors() {
      tftl::vector<int> vInt;
      tftl::vector<char> vChar;
      tftl::vector<double> vDouble;
      tftl::vector<SomeType> vCustom;
    }

    static void testMethods() {
      tftl::vector<int> result = {1, 2, 3, 4};

      result.max_size();
      result.shrink_to_fit();
      REQUIRE_FALSE(result.empty());
      REQUIRE(result.size() == 4);
      REQUIRE(result.capacity() == result.size());
      REQUIRE(result.at(3) == result[3]);
      REQUIRE(result.at(3) == result[3]);
      REQUIRE(*result.data() == result.front());
      result.insert(result.begin(), 1);
      result.insert(result.begin() + 1, 2, 2);
      result.assign(3, 5);
      result.pop_back();
      result.push_back(6);
      result.erase(result.begin() + 2, result.end());
      REQUIRE(result.size() == 2);
      result.clear();
      REQUIRE(result.empty());
      result.get_allocator();
      result.resize(5);
      result.resize(10, 2);
      result.reserve(100);
      REQUIRE(result.capacity() >= 100);
    }
  };

  SECTION("Working with different types") {
    REQUIRE_NOTHROW(SomeType::initVectors());
  }

  SECTION("Each method throw no exceptions by default") {
    REQUIRE_NOTHROW(SomeType::testMethods());
  }

  SECTION("Exception on copy") {
    tftl::vector<Error> result(1, Error());
    REQUIRE_THROWS(result.push_back(Error()));
  }

  SECTION("Out of range") {
    tftl::vector<int> result = {1, 2, 3};
    REQUIRE_THROWS(result.at(3));
  }

  SECTION("Invalid reserve") {
    tftl::vector<int> result;
    REQUIRE_THROWS(result.reserve((size_t) (-1)));
  }

}

TEST_CASE("Object destruction with vector") {

  static bool isDestroyed = false;

  struct Destroyable {
    ~Destroyable() {
      isDestroyed = true;
    }
  };

  SECTION("vector resize") {
    tftl::vector<Destroyable> result(5);
    isDestroyed = false;
    result.resize(3);
    REQUIRE(isDestroyed);
  }

  SECTION("vector erase") {
    tftl::vector<Destroyable> result(5);
    isDestroyed = false;
    result.erase(result.begin() + 1);
    REQUIRE(isDestroyed);
  }

  SECTION("vector erase range") {
    tftl::vector<Destroyable> result(5);
    isDestroyed = false;
    result.erase(result.begin() + 1, result.end());
    REQUIRE(isDestroyed);
  }

}

TEST_CASE("Iterator tests") {

  SECTION("Forward iteration") {
    std::vector<int> expected = {1, 2, 3, 4};
    tftl::vector<int> result = {1, 2, 3, 4};
    int i = 0;
    for (tftl::vector<int>::iterator it = result.begin(); it != result.end(); ++it, ++i) {
      REQUIRE(*it == expected[i]);
    }
  }

  SECTION("Backward iteration") {
    std::vector<int> expected = {1, 2, 3, 4};
    int i = 3;
    tftl::vector<int> result = {1, 2, 3, 4};
    for (tftl::vector<int>::iterator it = result.end() - 1; it >= result.begin(); --it, --i) {
      REQUIRE(*it == expected[i]);
    }
  }

  SECTION("Random access") {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    tftl::vector<int> result = {1, 2, 3, 4, 5};
    tftl::vector<int*> a;
    int b = 8;
    a.push_back(&b);
    REQUIRE(**(a.begin().operator->()) == 8);
    REQUIRE(*(result.begin() + 2) == *(expected.begin() + 2));
    REQUIRE(*(result.end() - 2) == *(result.end() - 2));
    REQUIRE(result.begin()[2] == expected.begin()[2]);
    tftl::vector<int>::iterator it = result.begin();
    std::vector<int>::iterator expectedIt = expected.begin();
    expectedIt += 2;
    it += 2;
    REQUIRE(*it == *expectedIt);
    expectedIt -= 2;
    it -= 2;
    REQUIRE(*it == *expectedIt);
    expectedIt++;
    it++;
    REQUIRE(*it == *expectedIt);
    expectedIt--;
    it--;
    REQUIRE(*it == *expectedIt);
  }

  SECTION("Comparision") {
    tftl::vector<int> result = {1, 2, 3, 4, 5};
    tftl::vector<int>::iterator first = result.begin();
    tftl::vector<int>::iterator last = result.end();
    REQUIRE(first < last);
    REQUIRE(first == first);
    REQUIRE(last > first);
    REQUIRE(last >= last);
    REQUIRE(last >= first);
    REQUIRE(first <= last);
    REQUIRE(first <= first);
    REQUIRE(first != last);
  }
}

TEST_CASE("Modifier elements methods") {
  SECTION("Emplace in the head") {
    std::vector<int> expected = {9, 1, 2, 3};
    tftl::vector<int> result = {1, 2, 3};
    result.emplace(result.cbegin(), 9);
    REQUIRE(result.size() == expected.size());
    REQUIRE(result[0] == expected[0]);
  }
  SECTION("Emplace in the middle") {
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    tftl::vector<int> result = {1, 2, 3, 5, 6};
    result.emplace(result.begin() + 3, 4);
    REQUIRE(result.size() == expected.size());
    REQUIRE(result[3] == expected[3]);
  }
  SECTION("Emplace_back method") {
    std::vector<int> expected = {4, 2};
    tftl::vector<int> result = {4};
    result.emplace_back(2);
    REQUIRE(result.size() == expected.size());
    REQUIRE(result[1] == expected[1]);
  }
}