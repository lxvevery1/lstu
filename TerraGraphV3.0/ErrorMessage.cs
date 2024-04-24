using UnityEngine;
using TMPro;

public class ErrorMessage : MonoBehaviour
{
    [SerializeField] private TMP_Text streamableTextUI;


    private void Start()
    {
    }

    private void Update()
    {
    }


    public void ThrowError(string errorText)
    {
        streamableTextUI.SetText(errorText);

        Debug.LogError(errorText);
    }
}
