function breadthFirstSearch(root) {
    let queue = [{ node: root, level: 0 }];
    let currentLevel = 0;
    let line = "";

    while (queue.length > 0) {
        let item = queue.shift();

        // If the current node's level changes, print the line and reset
        if (item.level !== currentLevel) {
            console.log(line);
            line = "";
            currentLevel = item.level;
        }

        // Append the node's name to the current line
        line += `${' '.repeat(item.level * 2)}${getNodeName(item.node)} `;

        // Add children of the current node to the queue
        for (let i = 0; i < item.node.children.length; i++) {
            queue.push({ node: item.node.children[i], level: item.level + 1 });
        }
    }

    // Print the last line if it's not empty
    if (line !== "") {
        console.log(line);
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

// Start BFS from the document's root
breadthFirstSearch(document.documentElement);