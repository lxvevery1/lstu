using System.Collections.Generic;
using System.Text;
using TMPro;
using UnityEngine;
using static IncidenceGenerator;

public class UIManager : MonoBehaviour
{
    [SerializeField] private TMP_InputField adjacencyMatrixInputField;
    [SerializeField] private TMP_InputField incidenceLeft;
    [SerializeField] private TMP_InputField incidenceRight;
    [SerializeField] private ErrorMessage errorMessage;
    private Incidences incidences;


    // Called when the "Generate" button is clicked
    public void OnGenerateButtonClick()
    {
        string matrixText = adjacencyMatrixInputField.text;
        int[,] adjacencyMatrix = ParseAdjacencyMatrix(matrixText);
        if (adjacencyMatrix != null)
        {
            incidences = IncidenceGenerator.GenerateIncidenceLists(adjacencyMatrix);

            SetIncidenceToText(incidences.left, ref incidenceLeft);
            SetIncidenceToText(incidences.right, ref incidenceRight);
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
}
