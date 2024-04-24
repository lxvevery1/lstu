using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class GuideAnim : MonoBehaviour
{
    [SerializeField] private Sprite guideDefault;
    [SerializeField] private Sprite guideSpeaks;
    [SerializeField] private Sprite guidePointDown;
    [SerializeField] private Sprite guidePointStraight;
    [SerializeField] private Image guideRenderer;


    private Sprite guideSprite
    {
        get { return guideRenderer.sprite; }
        set { guideRenderer.sprite = value; }
    }
    private Coroutine currCoroutine;
    private DialogueSystem dialogueSys;


    private void Awake()
    {
        dialogueSys = FindObjectOfType<DialogueSystem>();
    }

    private void Start()
    {
        dialogueSys.OnDialogueStart += HandleDialogueStart;
        dialogueSys.OnDialogueEnd += HandleDialogueEnd;
    }

    private void OnDestroy()
    {
        dialogueSys.OnDialogueStart -= HandleDialogueStart;
        dialogueSys.OnDialogueEnd -= HandleDialogueEnd;
    }


    private void HandleDialogueStart(int dialogueNumber)
    {
        if (dialogueNumber == 3)
        {
            PlayAnim2(3f);
        }
        else if (dialogueNumber == 4)
        {
            PlayAnim3(3f);
        }
        else
        {
            PlayAnim1(3, 0.33f);
        }
    }

    private void HandleDialogueEnd(int dialogueNumber)
    {
        StopCoroutine(currCoroutine);
    }

    private void PlayAnim1(in int spritesSwitch, in float frameTime)
    {
        if (currCoroutine != null)
        {
            StopCoroutine(currCoroutine);
        }

        currCoroutine = StartCoroutine(DoCycleSpriteSwitch(guideSpeaks, spritesSwitch, frameTime));
    }

    private void PlayAnim2(in float frameTime)
    {
        if (currCoroutine != null)
        {
            StopCoroutine(currCoroutine);
        }

        currCoroutine = StartCoroutine(DoSpriteSwitch(guidePointDown, frameTime));
    }

    public void PlayAnim3(in float frameTime)
    {
        if (currCoroutine != null)
        {
            StopCoroutine(currCoroutine);
        }

        currCoroutine = StartCoroutine(DoSpriteSwitch(guidePointStraight, frameTime));
    }


    private IEnumerator DoCycleSpriteSwitch(Sprite sprite, int spritesSwitch, float frameTime)
    {
        for (int i = 0; i < spritesSwitch; i++)
        {
            guideSprite = sprite;

            yield return new WaitForSeconds(frameTime);

            guideSprite = guideDefault;

            yield return new WaitForSeconds(frameTime);
        }
    }

    private IEnumerator DoSpriteSwitch(Sprite sprite, float frameTime)
    {
        guideSprite = sprite;

        yield return new WaitForSeconds(frameTime);

        guideSprite = guideDefault;
    }
}
