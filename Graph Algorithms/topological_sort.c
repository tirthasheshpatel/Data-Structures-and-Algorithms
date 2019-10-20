// Topo Sort using BFS Traversal
topological_sort(N, adj[N][N]) {
    T = []
    visited = []
    in_degree = []
    for i = 0 to N {
        in_degree[i] = visited[i] = 0
    }

    for i = 0 to N {
        for j = 0 to N {
            if adj[i][j] is TRUE {
                in_degree[j] = in_degree[j] + 1
            }
        }
    }

    for i = 0 to N {
        if in_degree[i] is 0 {
            enqueue(Queue, i)
            visited[i] = TRUE
        }
    }

    while Queue is not Empty {
        vertex = get_front(Queue)
        dequeue(Queue)
        T.append(vertex)
        for j = 0 to N {
            if adj[vertex][j] is TRUE and visited[j] is FALSE {
                in_degree[j] = in_degree[j] - 1
                if in_degree[j] is 0 {
                    enqueue(Queue, j)
                    visited[j] = TRUE
                }
            }
        }
    }

    return T
}


// Topo Sort using DFS Traversal
T = []
visited = []

topological_sort( cur_vert, N, adj[][] ){
    visited[cur_vert] = true
    for i = 0 to N {
        if adj[cur_vert][i] is true and visited[i] is false {
            topological_sort(i)
        }
    }
    
    T.insert_in_beginning(cur_vert)
}
