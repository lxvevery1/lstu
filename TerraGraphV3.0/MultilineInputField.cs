using UnityEngine;
using TMPro;

public class MultilineInputField : TMP_InputField
{
    protected override void LateUpdate()
    {
        base.LateUpdate();

        // ������������� ������� ������� Enter
        if (isFocused && Input.GetKeyDown(KeyCode.Return))
        {
            // ��������� ����� ������ � ����� InputField
            text += "<br>";
            // ������������� ������ � ����� ������
            caretPosition = text.Length;
            // ������������� ��������� ������ � 0, ����� �� �������� ����� ������
            selectionAnchorPosition = selectionFocusPosition = caretPosition;
            // ��������� ��������� �������
            MoveTextEnd(false);
        }
    }
}
