#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h> // Para kmalloc
#include <linux/types.h> // Para struct list_head

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

// Define a cabeça da lista como uma variável global estática
static LIST_HEAD(birthday_list);

struct birthday *novo_no(int dia, int mes, int ano) {
    struct birthday *pessoa = kmalloc(sizeof(struct birthday), GFP_KERNEL);
    if (!pessoa) {
        printk(KERN_ERR "Falha na alocação de memória\n");
        return NULL;
    }
    pessoa->day = dia;
    pessoa->month = mes;
    pessoa->year = ano;
    INIT_LIST_HEAD(&pessoa->list); // Inicializa o membro 'list'
    return pessoa;
}

void mostrar_lista(struct list_head *head) {
    struct birthday *ptr;
    list_for_each_entry(ptr, head, list) {
        printk(KERN_INFO "Data: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }
}

/* Essa função é chamada quando o módulo é carregado. */
static int __init birthday_module_init(void) {
    printk(KERN_INFO "Loading Module\n");

    struct birthday *pessoa1, *pessoa2, *pessoa3, *pessoa4, *pessoa5;

    // 1. A lista vazia já foi criada com LIST_HEAD(birthday_list)

    // 2. Gerar algumas datas de aniversário e inserir na lista
    pessoa1 = novo_no(15, 3, 1990);
    if (pessoa1)
        list_add_tail(&pessoa1->list, &birthday_list);

    pessoa2 = novo_no(28, 6, 1985);
    if (pessoa2)
        list_add_tail(&pessoa2->list, &birthday_list);

    pessoa3 = novo_no(5, 11, 2001);
    if (pessoa3)
        list_add_tail(&pessoa3->list, &birthday_list);

    pessoa4 = novo_no(1, 1, 1978);
    if (pessoa4)
        list_add_tail(&pessoa4->list, &birthday_list);

    pessoa5 = novo_no(22, 9, 1995);
    if (pessoa5)
        list_add_tail(&pessoa5->list, &birthday_list);

    // 3. Mostrar a lista gerada no log
    printk(KERN_INFO "Lista de Aniversários:\n");
    mostrar_lista(&birthday_list);

    return 0;
}

/* Essa função é chamada quando o módulo é removido. */
static void __exit birthday_module_exit(void) {
    printk(KERN_INFO "Removing Module\n");

    // Excluir todos os nós da lista
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "Lista de aniversários removida e memória liberada.\n");
}

/* Macros para o registro dos pontos de entrada e saída do módulo. */
module_init(birthday_module_init);
module_exit(birthday_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthdate Module");
MODULE_AUTHOR("SGG");