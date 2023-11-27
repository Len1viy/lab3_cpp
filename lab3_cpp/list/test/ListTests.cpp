#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту задачу с разработчика

#include <List.h>
#include <catch2/catch.hpp>
#include <array>

TEST_CASE("List") {
  SECTION("Constructors") {
    SECTION("Default") {
      List<int> list;
      REQUIRE(list.size() == 0);
      REQUIRE(list.empty());
      REQUIRE(list.begin() == list.end());
    }
    SECTION("Fill") {
      const int size = 10;
      const int val = 7;
      List<int> list(size, val);
      REQUIRE(list.size() == size);
      for (auto & i : list) {
        REQUIRE(i == val);
      }
    }
    SECTION("Iter") {
      std::array<int, 6> arr {1, 2, 3, 4, 5, 6};
      List<int> list(arr.cbegin(), arr.cend());
      REQUIRE(list.size() == arr.size());
      REQUIRE(std::equal(list.cbegin(), list.cend(), arr.cbegin(), arr.cend()));
    }
    SECTION("Initializer List") {
      std::array<int, 6> arr {1, 2, 3, 4, 5, 6};
      List<int> list {1, 2, 3, 4, 5, 6};
      REQUIRE(list.size() == arr.size());
      REQUIRE(std::equal(list.cbegin(), list.cend(), arr.cbegin(), arr.cend()));
    }
    SECTION("Copy") {
      std::array<int, 6> arr {1, 2, 3, 4, 5, 6};
      List<int> list1(arr.cbegin(), arr.cend());
      List<int> list2(list1);
      REQUIRE(list2.size() == arr.size());
      REQUIRE(std::equal(list2.cbegin(), list2.cend(), arr.cbegin(), arr.cend()));
    }
    SECTION("Move") {
      std::array<int, 6> arr {1, 2, 3, 4, 5, 6};
      List<int> list1(arr.cbegin(), arr.cend());
      List<int> list2(std::move(list1));
      REQUIRE(list2.size() == arr.size());
      REQUIRE(std::equal(list2.cbegin(), list2.cend(), arr.cbegin(), arr.cend()));
    }
  }

  SECTION("Operators") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());

    SECTION("Copy =") {
      List<int> list1;
      list1 = list;
      REQUIRE(list1.size() == ref.size());
      REQUIRE(std::equal(list1.cbegin(), list1.cend(), ref.cbegin(), ref.cend()));
    }

    SECTION("Move =") {
      List<int> list1;
      list1 = std::move(list);
      REQUIRE(list1.size() == ref.size());
      REQUIRE(std::equal(list1.cbegin(), list1.cend(), ref.cbegin(), ref.cend()));
    }

    SECTION("Initializer List =") {
      List<int> list1;
      list1 = {1, 2, 3, 4, 5, 6};
      REQUIRE(list1.size() == ref.size());
      REQUIRE(std::equal(list1.cbegin(), list1.cend(), ref.cbegin(), ref.cend()));
    }

    SECTION("==") {
      List<int> list1(list);
      REQUIRE(list1 == list);
    }
  }

  SECTION("Accessors") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());

    SECTION("Front") {
      REQUIRE(list.front() == ref.front());
    }

    SECTION("Const Front") {
      const auto& list_ref = list;
      REQUIRE(list_ref.front() == ref.front());
    }

    SECTION("Back") {
      REQUIRE(list.back() == ref.back());
    }

    SECTION("Const Front") {
      const auto& list_ref = list;
      REQUIRE(list_ref.back() == ref.back());
    }
  }

  SECTION("Insert") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());
    List<std::unique_ptr<int>> uptr_list;
    for (auto i : ref) {
      uptr_list.emplace_back(new int {i});
    }
    const double val = 10.0;

    SECTION("Emplace") {
      auto iter = list.cbegin();
      ++iter;
      auto new_iter = list.emplace(iter, val);
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(*new_iter == val);
      ++new_iter;
      REQUIRE(new_iter == iter);
    }

    SECTION("Emplace Front") {
      list.emplace_front(val);
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(list.front() == val);
    }

    SECTION("Emplace Back") {
      list.emplace_back(val);
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(list.back() == val);
    }

    SECTION("Insert Copy") {
      auto iter = list.cbegin();
      ++iter;
      auto new_iter = list.insert(iter, static_cast<const int&>(val));
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(*new_iter == val);
      ++new_iter;
      REQUIRE(new_iter == iter);
    }

    SECTION("Insert Move") {
      auto iter = uptr_list.cbegin();
      ++iter;
      auto new_iter = uptr_list.insert(iter, std::make_unique<int>(val));
      REQUIRE(uptr_list.size() == ref.size() + 1);
      REQUIRE(**new_iter == val);
      ++new_iter;
      REQUIRE(new_iter == iter);
    }

    SECTION("Push Front Copy") {
      double val = 10.0;
      list.push_front(static_cast<const int&>(val));
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(list.front() == val);
    }

    SECTION("Push Front Move") {
      uptr_list.push_front(std::make_unique<int>(val));
      REQUIRE(uptr_list.size() == ref.size() + 1);
      REQUIRE(*uptr_list.front() == val);
    }

    SECTION("Push Back Copy") {
      list.push_back(static_cast<const int&>(val));
      REQUIRE(list.size() == ref.size() + 1);
      REQUIRE(list.back() == val);
    }

    SECTION("Push Back Move") {
      uptr_list.push_back(std::make_unique<int>(val));
      REQUIRE(uptr_list.size() == ref.size() + 1);
      REQUIRE(*uptr_list.back() == val);
    }

    SECTION("Insert Duplcates") {
      const int cnt = 10;
      auto iter = list.cbegin();
      ++iter;
      auto new_iter = list.insert(iter, cnt, val);
      REQUIRE(list.size() == ref.size() + cnt);
      for (auto i = ++list.cbegin(); i != new_iter; ++i) {
        REQUIRE(*i == val);
      }
      REQUIRE(*new_iter == val);
      ++new_iter;
      REQUIRE(new_iter == iter);
    }

    SECTION("Insert Range") {
      auto iter = list.cbegin();
      ++iter;
      auto new_iter = list.insert(iter, ref.cbegin(), ref.cend());
      REQUIRE(list.size() == ref.size()*2);
      ++new_iter;
      REQUIRE(new_iter == iter);
      REQUIRE(std::equal(++list.begin(), new_iter, ref.cbegin(), ref.cend()));
    }

    SECTION("Insert Initializer List") {
      auto iter = list.cbegin();
      ++iter;
      auto new_iter = list.insert(iter, {1, 2, 3, 4, 5, 6});
      REQUIRE(list.size() == ref.size()*2);
      ++new_iter;
      REQUIRE(new_iter == iter);
      REQUIRE(std::equal(++list.begin(), new_iter, ref.cbegin(), ref.cend()));
    }
  }

  SECTION("Assign") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list({2, 3, 4, 5, 6, 7});
    const int cnt = 10;
    const int val = 10;

    SECTION("Assign Duplcates") {
      list.assign(cnt, val);
      REQUIRE(list.size() == cnt);
      for (auto i : list) {
        REQUIRE(i == val);
      }
    }

    SECTION("Assign Range") {
      list.assign(ref.cbegin(), ref.cend());
      REQUIRE(std::equal(list.cbegin(), list.cend(), ref.cbegin(), ref.cend()));
    }

    SECTION("Assign Initializer List") {
      list.assign({1, 2, 3, 4, 5, 6});
      REQUIRE(std::equal(list.cbegin(), list.cend(), ref.cbegin(), ref.cend()));
    }
  }

  SECTION("Auxilary") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());

    SECTION("Size") {
      REQUIRE(list.size() == ref.size());
    }

    SECTION("Max Size") {
      REQUIRE(list.max_size() >= list.size());
    }

    SECTION("Empty") {
      List<int> list1;
      REQUIRE_FALSE(list.empty());
      REQUIRE(list1.empty());
    }

    SECTION("Swap") {
      std::array<int, 4> ref1 {7, 8, 9, 10};
      List<int> list1(ref1.cbegin(), ref1.cend());
      list.swap(list1);
      REQUIRE(std::equal(list1.cbegin(), list1.cend(), ref.cbegin(), ref.cend()));
      REQUIRE(std::equal(list.cbegin(), list.cend(), ref1.cbegin(), ref1.cend()));
    }
  }

  SECTION("Erase") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());

    SECTION("Single") {
      auto iter = ++list.cbegin();
      auto new_iter = list.erase(iter);
      REQUIRE(list.size() == ref.size() - 1);
      REQUIRE(*new_iter == ref[2]);
      REQUIRE(++list.cbegin() == new_iter);
    }

    SECTION("Range") {
      auto begin = ++list.cbegin();
      auto end = begin;
      ++++end;
      auto new_iter = list.erase(begin, end);
      REQUIRE(list.size() == ref.size() - 2);
      REQUIRE(*new_iter == ref[3]);
      REQUIRE(++list.cbegin() == new_iter);
    }

    SECTION("Pop Back") {
      list.pop_back();
      REQUIRE(list.size() == ref.size() - 1);
      REQUIRE(std::equal(list.cbegin(), list.cend(), ref.cbegin(), ref.cend() - 1));
    }

    SECTION("Pop Front") {
      list.pop_front();
      REQUIRE(list.size() == ref.size() - 1);
      REQUIRE(std::equal(list.cbegin(), list.cend(), ref.cbegin() + 1, ref.cend()));
    }

    SECTION("Clear") {
      list.clear();
      REQUIRE(list.size() == 0);
      REQUIRE(list.empty());
      REQUIRE(list.begin() == list.end());
    }
  }

  SECTION("Iterator") {
    std::array<int, 6> ref {1, 2, 3, 4, 5, 6};
    List<int> list(ref.cbegin(), ref.cend());

    SECTION("Default Construct") {
      List<int>::iterator it;
    }

    SECTION("Copy Construct") {
      List<int>::iterator it = list.begin();
      List<int>::iterator it1(it);
      REQUIRE(it == it1);
    }

    SECTION("Assign") {
      List<int>::iterator it = list.begin();
      List<int>::iterator it1 = list.end();
      it1 = it;
      REQUIRE(it == it1);
    }

    SECTION("Dereference") {
      List<int>::iterator it = list.begin();
      REQUIRE(*it == list.front());
    }

    SECTION("Arrow") {
      List<std::array<int, 6>> arr_list {ref};
      auto it = arr_list.begin();
      REQUIRE(it->front() == ref.front());
    }

    SECTION("Compare") {
      List<int>::iterator it = list.begin();
      List<int>::iterator it1 = list.begin();
      List<int>::iterator it2 = list.end();
      REQUIRE(it == it1);
      REQUIRE(it != it2);
    }

    SECTION("Prefix Inc") {
      List<int>::iterator it1 = list.begin();
      List<int>::iterator it2 = list.begin();
      REQUIRE(it1 == it2);
      ++it1;
      REQUIRE(it1 != it2);
      ++it2;
      REQUIRE(it1 == it2);
    }

    SECTION("Postfix Inc") {
      List<int>::iterator it1 = list.begin();
      List<int>::iterator it2 = list.begin();
      REQUIRE(it1 == it2);
      it1++;
      REQUIRE(it1 != it2);
      it2++;
      REQUIRE(it1 == it2);
    }

    SECTION("Prefix Dec") {
      List<int>::iterator it1 = list.begin();
      List<int>::iterator it2 = list.begin();
      ++it1;
      ++it2;
      REQUIRE(it1 == it2);
      --it1;
      REQUIRE(it1 != it2);
      --it2;
      REQUIRE(it1 == it2);
    }

    SECTION("Postfix Dec") {
      List<int>::iterator it1 = list.begin();
      List<int>::iterator it2 = list.begin();
      it1++;
      it2++;
      REQUIRE(it1 == it2);
      it1--;
      REQUIRE(it1 != it2);
      it2--;
      REQUIRE(it1 == it2);
    }
  }
}
