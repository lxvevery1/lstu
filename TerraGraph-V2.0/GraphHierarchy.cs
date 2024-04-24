using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GraphHierarchy : MonoBehaviour
{
    [SerializeField] private AlgoManager uiManager;
    [SerializeField] private TMP_InputField adjacencyMatrixInputField;
    private readonly int[,] adjacencyMatrix;


    private void Start()
    {
        // ���������� �������������� ���������� � ���������� ���������� �������
        Dictionary<int, int> vertexOrder = AssignOrder(uiManager.ParseAdjacencyMatrix(adjacencyMatrixInputField.text));

        // ����� ����� � ������ ������� ������
        Debug.Log("������ ����� -> ����� �����");
        foreach (var entry in vertexOrder)
        {
            Debug.Log(entry.Key + " -> " + entry.Value);
        }

        // ������������� ������ ����� � ������ �������� ������
        Debug.Log("����� ����:");
        for (int i = 0; i < adjacencyMatrix.GetLength(0); i++)
        {
            List<int> neighbors = GetNeighbors(adjacencyMatrix, i);
            List<int> newNeighbors = new List<int>();
            foreach (int neighbor in neighbors)
            {
                newNeighbors.Add(vertexOrder[neighbor]);
            }
            Debug.Log(vertexOrder[i] + " -> " + string.Join(", ", newNeighbors));
        }
    }


    // ������� ���������� ���������� ������� ��������
    private Dictionary<int, int> AssignOrder(int[,] matrix)
    {
        List<int> topologicalOrder = TopologicalSort(matrix);
        Dictionary<int, int> vertexOrder = new Dictionary<int, int>();
        for (int i = 0; i < topologicalOrder.Count; i++)
        {
            vertexOrder[topologicalOrder[i]] = i + 1; // ��������� ���������� � 1
        }
        return vertexOrder;
    }

    // ������� �������������� ����������
    private List<int> TopologicalSort(int[,] matrix)
    {
        List<int> result = new List<int>();
        HashSet<int> visited = new HashSet<int>();

        for (int i = 0; i < matrix.GetLength(0); i++)
        {
            if (!visited.Contains(i))
            {
                DFS(matrix, i, visited, result);
            }
        }

        result.Reverse(); // ��������� ��������� ������ - ������������� ������������� ������
        return result;
    }

    // ����� � ������� ��� �������������� ����������
    private void DFS(int[,] matrix, int vertex, HashSet<int> visited, List<int> result)
    {
        visited.Add(vertex);
        for (int i = 0; i < matrix.GetLength(1); i++)
        {
            if (matrix[vertex, i] == 1 && !visited.Contains(i))
            {
                DFS(matrix, i, visited, result);
            }
        }
        result.Add(vertex);
    }

    // ��������� ������ ������� �������
    private List<int> GetNeighbors(int[,] matrix, int vertex)
    {
        List<int> neighbors = new List<int>();
        for (int i = 0; i < matrix.GetLength(1); i++)
        {
            if (matrix[vertex, i] == 1)
            {
                neighbors.Add(i);
            }
        }
        return neighbors;
    }

}
