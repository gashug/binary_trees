#include "binary_trees.h"

/**
 * avl_remove - Removes a node from an AVL tree.
 * @root: A pointer to the root node of the tree.
 * @value: The value to remove from the tree.
 *
 * Return: A pointer to the new root node of the tree.
 */
avl_t *avl_remove(avl_t *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->n)
        root->left = avl_remove(root->left, value);
    else if (value > root->n)
        root->right = avl_remove(root->right, value);
    else {
        if (root->left == NULL || root->right == NULL) {
            avl_t *child = root->left ? root->left : root->right;
            if (child == NULL) {
                child = root;
                root = NULL;
            } else {
                *root = *child;
            }
            free(child);
        } else {
            avl_t *successor = root->right;
            while (successor->left != NULL)
                successor = successor->left;

            root->n = successor->n;

            root->right = avl_remove(root->right, successor->n);
        }
    }

    if (root == NULL)
        return NULL;

    root->height = 1 + max(avl_height(root->left), avl_height(root->right));
    int balance = avl_balance(root);

    if (balance > 1 && avl_balance(root->left) >= 0)
        return binary_tree_rotate_right(root);
    if (balance > 1 && avl_balance(root->left) < 0) {
        root->left = binary_tree_rotate_left(root->left);
        return binary_tree_rotate_right(root);
    }
    if (balance < -1 && avl_balance(root->right) <= 0)
        return binary_tree_rotate_left(root);
    if (balance < -1 && avl_balance(root->right) > 0) {
        root->right = binary_tree_rotate_right(root->right);
        return binary_tree_rotate_left(root);
    }

    return root;
}
