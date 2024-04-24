using UnityEngine;

public abstract class Singleton<T> : MonoBehaviour where T : Singleton<T>
{
#pragma warning disable 0649

    [SerializeField] private bool dontDestroyOnLoad;

#pragma warning restore 0649

    private static T _Instance;

    public static T Instance
    {
        get
        {
            return _Instance;
        }
    }

    void Awake()
    {
        if (_Instance == null)
        {
            _Instance = this as T;
            if (dontDestroyOnLoad)
            {
                DontDestroyOnLoad(gameObject);
            }
            AwakeSingleton();
        }
        else
        {
            Destroy(gameObject.GetComponent<T>());
        }
    }
    protected virtual void AwakeSingleton() { }
}