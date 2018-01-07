#include <iostream>
#include <cassert>


struct List
{
    int num;
    char sign;

    List *next_elem = nullptr;
};

void List_print(const List *list) {
    const List * curr_elem = list;
    while (curr_elem) {
        std::cout << "num: " << curr_elem->num
                  << " sign: " << curr_elem->sign << "\n";
        curr_elem = curr_elem->next_elem;
    }
}

void List_push_back(List *list, List *new_elem) {
    assert(list);
    while (list->next_elem)
        list = list->next_elem;
    list->next_elem = new_elem;
}

List * List_get_elem(List *list, unsigned pos) {
    assert(list);
    List *result = list;
    for (unsigned i = 0; i < pos; ++i) {
        assert(result->next_elem);
        result = result->next_elem;
    }

    return result;
}

void List_push_after(List *list, List *to_push, unsigned pos) {
    assert(list);
    List *one_before = List_get_elem(list, pos);
    List *old_val = one_before->next_elem;
    one_before->next_elem = to_push;
    to_push->next_elem = old_val;
}

void List_free(List *list) {
    if (list->next_elem)
        List_free(list->next_elem);

    delete list;
}

int main()
{
    List *list = nullptr;
 
    // 1
    for (int i = 0; i < 4; ++i) {
        List *curr_elem = new List;
        std::cin >> curr_elem->num >> curr_elem->sign;
        if (!list)
            list = curr_elem;
        else
            List_push_back(list, curr_elem);
    }

    // 2
    List_print(list);
    std::cout << std::endl;

    // 3
    {
        const List *first = List_get_elem(list, 0);
        const List *second = List_get_elem(list, 1);
        List *sum = new List;
        sum->num = first->num + second->num;
        sum->sign = 's';
        List_push_after(list, sum, 1);
    }

    {
        const List *one_before_last = List_get_elem(list, 3);
        const List *last = List_get_elem(list, 4);
        List *diff = new List;
        diff->num = one_before_last->num - last->num;
        diff->sign = 'r';
        List_push_after(list, diff, 4);
    }

    // 4
    List_print(list);
    std::cout << std::endl;

    // 5
    List_free(list);
    list = nullptr;

    // 6
    List_print(list);
}