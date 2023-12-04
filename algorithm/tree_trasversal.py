class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self, root):
        self.root = TreeNode(root)

    def inorder_traversal(self):
        result = []
        stack = []
        current = self.root

        while current or stack:
            while current:
                stack.append(current)
                current = current.left

            current = stack.pop()
            result.append(current.value)
            current = current.right

        return result

    def preorder_traversal(self):
        result = []
        stack = [self.root]

        while stack:
            current = stack.pop()
            if current:
                result.append(current.value)
                stack.append(current.right)
                stack.append(current.left)

        return result

    def postorder_traversal(self): # tricky put in res in reverse order in stack
        # put first left then right
        result = []
        stack = [self.root]

        while stack:
            current = stack.pop()
            if current:
                result.insert(0, current.value)
                stack.append(current.left)
                stack.append(current.right)

        return result

# Example usage:
# Creating a simple binary tree:   1
#                                 / \
#                                2   3
#
tree = BinaryTree(1)
tree.root.left = TreeNode(2)
tree.root.right = TreeNode(3)

# In-order traversal: [2, 1, 3]
print("In-order traversal:", tree.inorder_traversal())

# Pre-order traversal: [1, 2, 3]
print("Pre-order traversal:", tree.preorder_traversal())

# Post-order traversal: [2, 3, 1]
print("Post-order traversal:", tree.postorder_traversal())
