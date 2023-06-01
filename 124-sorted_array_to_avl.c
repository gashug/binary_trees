#include "binary_trees.h"

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array.
 * @array: A pointer to the first element of the array.
 * @size: The number of elements in the array.
 *
 * Return: A pointer to the root node of the created AVL tree,
 *         or NULL on failure.
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
    if (array == NULL || size == 0)
        return NULL;

    return build_avl_tree(array, 0, size - 1);
}

/**
 * build_avl_tree - Recursively builds an AVL tree from a sorted array.
 * @array: A pointer to the first element of the array.
 * @start: The starting index of the current subarray.
 * @end: The ending index of the current subarray.
 *
 * Return: A pointer to the root node of the created AVL tree,
 *         or NULL on failure.
 */
avl_t *build_avl_tree(int *array, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = start + (end - start) / 2;
    avl_t *root = binary_tree_node(NULL, array[mid]);
    if (root == NULL)
        return NULL;

    root->left = build_avl_tree(array, start, mid - 1);
    root->right = build_avl_tree(array, mid + 1, end);

    root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    return root;
}

/**
 * binary_tree_node - Creates a binary tree node.
 * @parent: A pointer to the parent of the node to create.
 * @value: The value to put in the new node.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
    binary_tree_t *new;

    new = malloc(sizeof(binary_tree_t));
    if (new == NULL)
        return NULL;

    new->n = value;
    new->parent = parent;
    new->left = NULL;
    new->right = NULL;
    new->height = 0;

    return new;
}

/**
 * avl_height - Measures the height of an AVL tree.
 * @tree: A pointer to the root node of the tree.
 *
 * Return: The height of the tree, or 0 if tree is NULL.
 */
size_t avl_height(const binary_tree_t *tree)
{
    if (tree == NULL)
        return 0;

    return tree->height;
}

/**
 * max - Returns the maximum of two numbers.
 * @a: The first number.
 * @b: The second number.
 *
 * Return: The maximum of a and b.
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}
