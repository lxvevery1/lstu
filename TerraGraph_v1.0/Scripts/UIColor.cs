using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class UIColor : MonoBehaviour
{
    [SerializeField] private Image matrix;
    [SerializeField] private Image genButton;

    private Color defColor;
    private Color darkerColor;
    private DialogueSystem dialogueSys;

    private void Awake()
    {
        dialogueSys = FindObjectOfType<DialogueSystem>();

        defColor = matrix.color;
        darkerColor = Color.HSVToRGB(239, 58+15, 54+15);

        

        genButton.color = defColor;

        dialogueSys.OnDialogueStart += HandleDialogueStart;
    }

    private void HandleDialogueStart(int dialogueNumber)
    {
        if (dialogueNumber == 3)
        {
            StartCoroutine(DoColorBlink(matrix));
        }
        else if (dialogueNumber == 4)
        {
            StartCoroutine(DoColorBlink(genButton));
        }
    }

    private IEnumerator DoColorBlink(Image image)
    {
        float duration = 1.5f;
        int iterations = 9;

        for (int i = 0; i < iterations; i++)
        {
            yield return SmoothTransitionCoroutine(image, i % 2 == 0 ? defColor : darkerColor, duration / 2f);
        }
    }

    private IEnumerator SmoothTransitionCoroutine(Image image, Color targetValue, float duration)
    {
        Color startColor = image.color;
        float timer = 0f;

        while (timer < duration)
        {
            timer += Time.deltaTime;
            float t = timer / duration;
            image.color = Color.Lerp(startColor, targetValue, t);
            yield return new WaitForEndOfFrame();
        }

        image.color = targetValue;
    }
}
