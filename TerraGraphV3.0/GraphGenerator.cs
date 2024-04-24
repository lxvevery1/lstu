using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
/*
 
Adjacency matrix:

0 1 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 
0 1 0 0 0 0 0 0 0 1 
0 0 1 0 1 0 0 1 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 1 
0 0 0 0 0 1 0 1 0 0 
0 0 0 0 0 0 0 0 1 0 
1 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 1 0 

*/
public class GraphGenerator : MonoBehaviour
{
    List<Edge> E;
    List<Subgraph> Subgr = new List<Subgraph>();

    public static List<Subgraph> TopologicalDecomposition(int countV, List<Edge> E, List<Subgraph> Sub)
    {
        List<int> notUsedV = new List<int>(); //список еще не использованных вершин
        for (int i = 0; i < countV; i++)
            notUsedV.Add(i);
        while (notUsedV.Count > 0)
        {
            List<int> R = new()  //достижимое множество
            {
                notUsedV[0]
            };
            List<int> Q = new() //контрдостижимое множество
            {
                notUsedV[0]
            };
            int[] color = new int[countV];
            //формируем достижимое и контрдостижимое множества
            for (int i = 1; i < notUsedV.Count; i++)
            {
                for (int k = 0; k < countV; k++)
                {
                    if (notUsedV.IndexOf(k) != -1)
                        color[k] = 1;
                    else
                        color[k] = 2;
                }
                if (DFS(notUsedV[0], notUsedV[i], E, color)) R.Add(notUsedV[i]);
                for (int k = 0; k < countV; k++)
                {
                    if (notUsedV.IndexOf(k) != -1)
                        color[k] = 1;
                    else
                        color[k] = 2;
                }
                if (DFS(notUsedV[i], notUsedV[0], E, color)) Q.Add(notUsedV[i]);
            }
            //пересечение множеств R и Q
            List<int> intersection = new List<int>(R.Intersect(Q).ToList());
            Sub.Add(new Subgraph(intersection, SubEdges(E, intersection)));
            for (int i = 0; i < intersection.Count; i++)
            {
                notUsedV.Remove(intersection[i]);
            }
        }
        return Sub;
    }



    /// <summary> Generate list of edges for adjacency matrix </summary>
    public static List<Edge> ListEdges(int[,] adjacencyMatrix)
    {
        List<Edge> edges = new List<Edge>();

        int rows = adjacencyMatrix.GetLength(0);
        int cols = adjacencyMatrix.GetLength(1);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (adjacencyMatrix[i, j] != 0)
                {
                    edges.Add(new Edge(i, j));
                }
            }
        }

        return edges;
    }

    public static int[,] IncidenceMatrixV(List<Subgraph> subgraphs)
    {
        int numVertices = 0;
        foreach (Subgraph subgraph in subgraphs)
        {
            numVertices += subgraph.V.Count;
        }

        int numEdges = 0;
        foreach (Subgraph subgraph in subgraphs)
        {
            numEdges += subgraph.E.Count;
        }

        int[,] incidenceMatrix = new int[numVertices, numEdges];

        int vertexIndex = 0;
        int edgeIndex = 0;

        foreach (Subgraph subgraph in subgraphs)
        {
            foreach (int vertex in subgraph.V)
            {
                foreach (Edge edge in subgraph.E)
                {
                    if (edge.v1 == vertex)
                    {
                        incidenceMatrix[vertexIndex, edgeIndex] = -1;
                    }
                    else if (edge.v2 == vertex)
                    {
                        incidenceMatrix[vertexIndex, edgeIndex] = 1;
                    }
                    else
                    {
                        incidenceMatrix[vertexIndex, edgeIndex] = 0;
                    }
                    edgeIndex++;
                }
                vertexIndex++;
                edgeIndex = 0;
            }
        }

        return incidenceMatrix;
    }

    public static int[,] IncidenceMatrix(List<Subgraph> subgraphs, List<Edge> initialEdges)
    {
        // Count the number of subgraphs and initial edges
        int numSubgraphs = subgraphs.Count;
        int numInitialEdges = initialEdges.Count;

        // Count the total number of edges in all subgraphs
        int numTotalEdges = 0;
        foreach (Subgraph subgraph in subgraphs)
        {
            numTotalEdges += subgraph.E.Count;
        }

        // Total number of edges includes initial edges and edges within subgraphs
        int totalEdgesCount = numInitialEdges + numTotalEdges;

        // Create incidence matrix with appropriate dimensions
        int[,] incidenceMatrix = new int[numSubgraphs, totalEdgesCount];

        // Initialize indices for subgraphs and edges
        int subgraphIndex = 0;
        int edgeIndex = 0;

        // Process subgraphs
        foreach (Subgraph subgraph in subgraphs)
        {
            // Process edges within subgraph
            foreach (Edge edge in subgraph.E)
            {
                incidenceMatrix[subgraphIndex, edgeIndex] = 1;
                edgeIndex++;
            }

            // Process initial edges
            foreach (Edge initialEdge in initialEdges)
            {
                // Check if initial edge connects to the current subgraph
                if (subgraph.V.Contains(initialEdge.v1) && subgraph.V.Contains(initialEdge.v2))
                {
                    incidenceMatrix[subgraphIndex, edgeIndex] = 1;
                    edgeIndex++;
                }
            }

            // Reset edge index for next subgraph
            edgeIndex = 0;
            subgraphIndex++;
        }

        return incidenceMatrix;
    }



    private static bool DFS(int u, int endV, List<Edge> E, int[] color)
    {
        color[u] = 2;
        if (u == endV)
        {
            return true;
        }
        for (int w = 0; w < E.Count; w++)
        {
            if (color[E[w].v2] == 1 && E[w].v1 == u)
            {
                if (DFS(E[w].v2, endV, E, color)) return true;
                color[E[w].v2] = 1;
            }
        }
        return false;
    }

    private static List<Edge> SubEdges(List<Edge> origEdges, List<int> intersections)
    {
        List<Edge> subedges = new();

        if (intersections.Count == 1)
            return subedges;

        foreach (Edge origEdge in origEdges)
        {
            for (int i = 0; i < intersections.Count; i++)
            {
                for (int j = 0; j < intersections.Count; j++)
                {
                    if (intersections[i] == origEdge.v1 && intersections[j] == origEdge.v2)
                    {
                        Edge newEdge = new Edge(origEdge.v1, origEdge.v2);
                        if (!subedges.Contains(newEdge))
                            subedges.Add(newEdge);
                    }
                }
            }
        }

        return subedges;
    }

    // план: 1. сначала нужно найти множество неиспользованных дуг, затем понять какая дуга какие подграфы соединяет и получить итоговую матрицу инциденций

    // 1. Нашли множество неиспользованных дуг
    public static List<Edge> GetUnusedEdges(List<Edge> origEdges, List<Subgraph> subgr, ref List<Edge> usedEdges)
    {
        List<Edge> unusedEdges = new(origEdges);

        foreach (Subgraph subg in subgr)
        {
            usedEdges.AddRange(subg.E);
        }

        for (int i = 0; i < unusedEdges.Count; i++)
        {
            for (int j = 0; j < usedEdges.Count; j++)
            {
                if (unusedEdges[i].v1 == usedEdges[j].v1 && unusedEdges[i].v2 == usedEdges[j].v2)
                {
                    unusedEdges.RemoveAt(i);
                }
            }
        }

        return unusedEdges;
    }

    // 2. Теперь нужно узнать какая дуга соединяет соответствующие подграфы
    public static Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> GetConnectiveEdges(List<Edge> unusedEdges, List<Subgraph> subgraphs)
    {
        var connectiveEdges = new Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>>();

        foreach (var edge in unusedEdges)
        {
            foreach (var subgraph1 in subgraphs)
            {
                foreach (var subgraph2 in subgraphs)
                {
                    if (subgraph1 != subgraph2)
                    {
                        if (subgraph1.V.Contains(edge.v1) && subgraph2.V.Contains(edge.v2))
                        {
                            connectiveEdges.Add(edge, new KeyValuePair<Subgraph, Subgraph>(subgraph1, subgraph2));
                            break;
                        }
                        if (subgraph1.V.Contains(edge.v2) && subgraph2.V.Contains(edge.v1))
                        {
                            connectiveEdges.Add(edge, new KeyValuePair<Subgraph, Subgraph>(subgraph2, subgraph1));
                            break;
                        }
                    }

                }
                if (connectiveEdges.ContainsKey(edge)) // Уже найдено соединение для этой дуги
                    break;
            }
        }

        connectiveEdges = RemoveLooseConnections(connectiveEdges);

        return connectiveEdges;
    }

    private static void GetSortedSubgraph1(Subgraph subgraph, Edge edge, ref Subgraph subgraphNew)
    {
        if (subgraph.V.Contains(edge.v1))
            subgraphNew = subgraph;
    }
    private static void GetSortedSubgraph2(Subgraph subgraph, Edge edge, ref Subgraph subgraphNew)
    {
        if (subgraph.V.Contains(edge.v2))
            subgraphNew = subgraph;
    }

    private static Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> RemoveLooseConnections(Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> connections)
    {
        var uniqueConnections = new Dictionary<KeyValuePair<Subgraph, Subgraph>, Edge>();
        var connectionsTemp = new Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>>(connections);
        // Проходимся по всем записям в словаре connections
        foreach (var pair in connectionsTemp)
        {
            Edge edge = pair.Key;
            KeyValuePair<Subgraph, Subgraph> subgraphPair = pair.Value;

            // Составляем уникальный ключ на основе пары подграфов
            var key = new KeyValuePair<Subgraph, Subgraph>(subgraphPair.Key, subgraphPair.Value);

            // Если такой ключ уже есть в словаре, удаляем ребро из connections
            if (uniqueConnections.ContainsKey(key))
            {
                // Удаляем текущее ребро, так как уже есть ребро, соединяющее эти два подграфа
                connections.Remove(edge);
            }
            else
            {
                // Добавляем текущее ребро в словарь uniqueConnections с уникальным ключом
                uniqueConnections.Add(key, edge);
            }
        }

        return connections;
    }

    public static int[,] CreateSubgraphIncidenceMatrix(Dictionary<Edge, KeyValuePair<Subgraph, Subgraph>> connections, List<Subgraph> subgraphs)
    {
        // Создаем матрицу инцидентности
        int[,] incidenceMatrix = new int[subgraphs.Count, connections.Count];

        // Проходим по каждому ребру
        int edgeIndex = 0;
        foreach (var edgeConnection in connections)
        {
            var edge = edgeConnection.Key;
            var subgraphPair = edgeConnection.Value;

            // Находим индексы подграфов, к которым принадлежит данное ребро
            int subgraphIndex1 = subgraphs.IndexOf(subgraphPair.Key);
            int subgraphIndex2 = subgraphs.IndexOf(subgraphPair.Value);

            // Помечаем соответствующие ячейки матрицы инцидентности
            incidenceMatrix[subgraphIndex1, edgeIndex] = 1;
            incidenceMatrix[subgraphIndex2, edgeIndex] = -1;

            edgeIndex++;
        }

        return incidenceMatrix;
    }
}

[Serializable]
public class Edge
{
    public int v1, v2;

    public Edge(int v1, int v2)
    {
        this.v1 = v1;
        this.v2 = v2;
    }
}

[Serializable]
public class Subgraph
{
    public List<int> V;
    public List<Edge> E;

    public Subgraph()
    {
        V = new List<int>();
    }

    public Subgraph(List<int> V)
    {
        this.V = new List<int>(V);
    }

    public Subgraph(List<int> V, List<Edge> E)
    {
        this.V = new List<int>(V);
        this.E = new List<Edge>(E);
    }
}

