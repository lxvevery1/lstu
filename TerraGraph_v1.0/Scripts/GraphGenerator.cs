using System.Collections.Generic;
using UnityEngine;

public class GraphGenerator : MonoBehaviour
{
    [SerializeField] private GameObject nodePrefab;
    [SerializeField] private GameObject edgePrefab;


    private List<GameObject> nodes = new();
    private List<GameObject> edges = new();


    // Generate graph from adjacency matrix
    public void GenerateGraphFromMatrix(int[,] adjacencyMatrix)
    {
        int numNodes = adjacencyMatrix.GetLength(0);

        
        if (nodes.Count > 0) 
        { 
            // Clear previous graph
            foreach (var node in nodes)
            {
                Destroy(node);
            }
            nodes.Clear();
        }
        if (edges.Count > 0)
        {
            foreach (var edge in edges)
            {
                Destroy(edge);
            }
            edges.Clear();
        }
        
        // Create nodes
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (adjacencyMatrix[i, j] == 1)
                {
                    GameObject node1 = CreateNode(new Vector2(i * 2, j * 2));
                    GameObject node2 = CreateNode(new Vector2((i + 1) * 2, j * 2));
                    CreateEdge(node1, node2);
                }
            }
        }
    }


    // Create a node at the given position
    private GameObject CreateNode(Vector2 position)
    {
        GameObject node = Instantiate(nodePrefab, position, Quaternion.identity);
        nodes.Add(node);
        return node;
    }

    // Create an edge between two nodes
    private GameObject CreateEdge(GameObject node1, GameObject node2)
    {
        GameObject edge = Instantiate(edgePrefab, (node1.transform.position + node2.transform.position) / 2, Quaternion.identity);
        edge.transform.right = node2.transform.position - node1.transform.position;
        edge.transform.localScale = new Vector3(Vector2.Distance(node1.transform.position, node2.transform.position), 1f, 1f);
        edges.Add(edge);
        return edge;
    }
} 