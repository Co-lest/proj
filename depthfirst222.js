function depthFirstSearch(root) {
    let stack = [{ node: root, path: '' }];

    while (stack.length > 0) {
        let { node, path } = stack.pop();
        let nodeName = getNodeName(node);

        // Append the current node's name to the path
        let currentPath = path.length === 0 ? nodeName : `${path} > ${nodeName}`;

        // If the current node is a leaf node, print the path
        if (node.children.length === 0) {
            console.log(currentPath);
        } else {
            // Otherwise, push children with updated path to the stack
            for (let i = node.children.length - 1; i >= 0; i--) {
                stack.push({ node: node.children[i], path: currentPath });
            }
        }
    }
}

// Function to get the name of the node
function getNodeName(node) {
    switch(node.nodeType) {
        case Node.ELEMENT_NODE:
            return node.tagName;
        case Node.TEXT_NODE:
            return `Text: "${node.textContent.trim()}"`;
        case Node.COMMENT_NODE:
            return `<!-- ${node.textContent.trim()} -->`;
        default:
            return `Node Type ${node.nodeType}`;
    }
}

// Start DFS from the document's root
depthFirstSearch(document.documentElement);