using System.Collections.Generic;
using System.Text;
using TMPro;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    [SerializeField] private TMP_InputField adjacencyMatrixInputField;
    [SerializeField] private TMP_InputField incidenceMatrix;
    [SerializeField] private TMP_InputField subGraphsInfo;
    [SerializeField] private ErrorMessage errorMessage;
    private List<Edge> edges;
    private List<Edge> unusedEdges = new();
    private List<Edge> usedEdges = new();
    private List<Subgraph> subgr;
    private Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> connections = new();
    private int[,] incMatrix;


    private void Awake()
    {
        adjacencyMatrixInputField.text =
            "0 1 0 0 0 0 0 0 0 0 \r\n" +
            "0 0 0 0 0 0 1 0 0 0 \r\n" +
            "0 1 0 0 0 0 0 0 0 1 \r\n" +
            "0 0 1 0 1 0 0 1 0 0 \r\n" +
            "0 0 0 0 0 0 0 0 0 0 \r\n" +
            "0 0 0 0 1 0 0 0 0 1 \r\n" +
            "0 0 0 0 0 1 0 1 0 0 \r\n" +
            "0 0 0 0 0 0 0 0 1 0 \r\n" +
            "1 0 0 0 0 0 0 0 0 0 \r\n" +
            "0 0 0 0 0 0 0 0 1 0 ";

        incidenceMatrix.textComponent.alignment = TextAlignmentOptions.Center;
    }

    // Called when the "Generate" button is clicked
    public void OnGenerateButtonClick()
    {
        string matrixText = adjacencyMatrixInputField.text;
        int[,] adjacencyMatrix = ParseAdjacencyMatrix(matrixText);
        if (adjacencyMatrix != null)
        {
            edges = GraphGenerator.ListEdges(adjacencyMatrix);

            subgr = new();
            unusedEdges = new();
            usedEdges = new();
            connections = new();
            subgr = GraphGenerator.TopologicalDecomposition(adjacencyMatrix.GetLength(0), edges, subgr);

            unusedEdges = GraphGenerator.GetUnusedEdges(edges, subgr, ref usedEdges);
            connections = GraphGenerator.GetConnectiveEdges(unusedEdges, subgr);

            // incMatrix = GraphGenerator.GetIncidenceMatrix(edges, connections, subgr);
            incMatrix = GraphGenerator.CreateSubgraphIncidenceMatrix(connections, subgr);

            SetIncidenceToText(incMatrix, ref incidenceMatrix);
            PrintConnectiveEdges(connections);
        }
    }


    // Parse the adjacency matrix from the input field text
    private int[,] ParseAdjacencyMatrix(string text)
    {
        string[] lines = text.Trim().Split('\n');
        int numRows = lines.Length;
        int numCols = lines[0].Trim().Split(' ').Length;
        int[,] matrix = new int[numRows, numCols];

        if (numRows != numCols)
        {
            errorMessage.ThrowError("Adjacency matrix must be square (nxn)");
            return null;
        }

        for (int i = 0; i < numRows; i++)
        {
            string[] rowValues = lines[i].Trim().Split(' ');
            if (rowValues.Length != numCols)
            {
                errorMessage.ThrowError("Invalid number of elements in row " + (i + 1));
                return null;
            }

            for (int j = 0; j < numCols; j++)
            {
                if (!int.TryParse(rowValues[j], out matrix[i, j]))
                {
                    errorMessage.ThrowError("Invalid element at row " + (i + 1) + ", column " + (j + 1));
                    return null;
                }
            }
        }

        return matrix;
    }

    private void SetSubgraphToText(List<Subgraph> subs, ref TMP_InputField subsInfo)
    {
        // foreach ()
    }

    private void SetIncidenceToText(Dictionary<int, List<int>> incidence, ref TMP_InputField inputField)
    {
        StringBuilder stringBuilder = new StringBuilder();

        foreach (var kvp in incidence)
        {
            stringBuilder.Append($"G({kvp.Key}) = {{");
            for (int i = 0; i < kvp.Value.Count; i++)
            {
                stringBuilder.Append(kvp.Value[i]);
                if (i < kvp.Value.Count - 1)
                {
                    stringBuilder.Append("; ");
                }
            }
            stringBuilder.Append("}\n");
        }

        inputField.text = stringBuilder.ToString();
    }

    private void SetIncidenceToText(int[,] incidenceMatrix, ref TMP_InputField inputField)
    {
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < incidenceMatrix.GetLength(0); i++)
        {
            for (int j = 0; j < incidenceMatrix.GetLength(1); j++)
            {
                stringBuilder.Append(incidenceMatrix[i, j] + " ");
            }
            stringBuilder.Append("\n");
        }



        inputField.text = stringBuilder.ToString();
    }

    public static void PrintConnectiveEdges(Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> connectiveEdges)
    {
        foreach (var pair in connectiveEdges)
        {
            Edge edge = pair.Key;
            KeyValuePair<Subgraph, Subgraph> subgraphPair = pair.Value;
            Subgraph subgraph1 = subgraphPair.Key;
            Subgraph subgraph2 = subgraphPair.Value;

            Debug.Log($"Edge ({edge.v1}, {edge.v2}) connects Subgraph {string.Join(",", subgraph1.V)} and Subgraph {string.Join(",", subgraph2.V)}");
        }
    }

}
