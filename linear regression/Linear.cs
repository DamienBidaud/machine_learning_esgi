//using UnityEngine;
//using System.Collections;
//using System.Runtime.InteropServices;

//public class Linear : MonoBehaviour {

//    [DllImport("ConsoleApplication1")]
//    static extern public void createModel(int nbInput, double[] model);

//    [DllImport("ConsoleApplication1")]
//    static extern public void pal(double[] exemplValue, int size, int inputSize, double[] model, double[] waitValue,
//        double coef, int maxIter);

//    [DllImport("ConsoleApplication1")]
//    static extern public double perceptron(double[] value, double[] model, int size);

//    [DllImport("ConsoleApplication1")]
//    static extern public double[][] cleanArray(double[] value, int size, int sizeElement);

//    [DllImport("ConsoleApplication1")]
//    static extern public double lineaire_model(int[] w, int[] x, int sumLength);

//    [DllImport("ConsoleApplication1")]
//    static extern public void regresion(double[] valueSend, int size, int inputSize, double[] waitValue, double[] model);

//    [SerializeField]
//    private Transform[] trainingPanel;

//    [SerializeField]
//    private Transform[] panelValues;

//    //class LinearTraining2
//    //{
//    //    public int NbElements { get; set; }

//    //    public int NbInputs { get; set; }

//    //    public double[] TrainingExemples { get; set; }

//    //    public double[] ExpectedResults { get; set; }

//    //    public int MaxIteration { get; set; }
//    //}

//    //void adjustPlan2(double[] ptrModel)
//    //{

//    //    for (int i = 0; i < planTargetTransforms.Length; i++)
//    //    {
//    //        Transform t = planTargetTransforms[i].GetComponent<Transform>();
//    //        MeshRenderer mr = planTargetTransforms[i].GetComponent<MeshRenderer>();

//    //        double[] input = new double[2];
//    //        input[0] = t.position.x;
//    //        input[1] = t.position.z;
//    //        double val = classifyRegression(ptrModel, input, 2);

//    //        //t.position = new Vector3(t.position.x, (float)val, t.position.z);

//    //        val = (val + 1) / 2;


//    //        mr.material.color = new Color((float)val, 0f, (float)(1.0 - val));

//    //    }
//    //}

//    //void linearScenarioRegression(LinearTraining2 c, double[] model)
//    //{
//    //    regresion(model, c.NbInputs, c.NbElements, c.TrainingExemples, c.ExpectedResults);

//    //    adjustPlan2(model);
//    //}

//    // Use this for initialization
//    void Start () {
//        double[] model = new double[2];
//        createModel(2, model);

//        double[] exemple = new double[trainingPanel.Length * 2];
//        int pos = 0;
//        int i = 0;
//        while (pos < exemple.Length)
//        {
//            exemple[pos] = trainingPanel[i].position.x;
//            exemple[pos + 1] = trainingPanel[i].position.y;
//            i++;
//            pos = pos + 2;
//        }
//        double[] waitValues = new double[] { 1, 1, -1, -1 };
//        regresion(exemple, exemple.Length, 2, waitValues, model);
//        //for(int j=0; j<model.Length; j++)
//        //{

//        //}
//    }

//	// Update is called once per frame
//	void Update () {

//	}
//}

using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class Linear : MonoBehaviour
{

    [DllImport("ConsoleApplication1")]
    static extern public int Hello42();

    [DllImport("ConsoleApplication1")]
    static extern public void removeModel(System.IntPtr model);

    [DllImport("ConsoleApplication1")]
    static extern public System.IntPtr createModelLinear(int nbInput);

    [DllImport("ConsoleApplication1")]
    static extern public void trainPLA(double[] exemples, int nbInput, int nbExemples, int[] expectedResult, System.IntPtr model, int maxIteration);

    [DllImport("ConsoleApplication1")]
    static extern public void perceptron_regression(System.IntPtr model, double[] inputs, int nbInput, int nbCount, double[] expectedResult);


    [DllImport("ConsoleApplication1")]
    static extern public int classifyLinear(System.IntPtr model, double[] element, int nbInput);

    [DllImport("ConsoleApplication1")]
    static extern public double classifyRegression(System.IntPtr model, double[] element, int nbInput);


    [DllImport("ConsoleApplication1")]
    static extern public void trainRosenblatt(double[] exemples, int nbInput, int nbExemples, int[] expectedResult, System.IntPtr model, int maxIteration);

    [DllImport("ConsoleApplication1")]
    static extern public int classifyRosenblatt(System.IntPtr model, double[] element, int nbInput);

    [SerializeField]
    Transform[] planTargetTransforms;

    [SerializeField]
    Transform[] targetTransforms;

    [SerializeField]
    MeshRenderer[] targetMeshRenderers;

    [SerializeField]
    Material redMat;

    [SerializeField]
    Material blueMat;

    [SerializeField]
    Material greenMat;

    class LinearTraining
    {
        public int NbElements { get; set; }

        public int NbInputs { get; set; }

        public double[] TrainingExemples { get; set; }

        public int[] ExpectedResults { get; set; }

        public int MaxIteration { get; set; }
    }
    class LinearTraining2
    {
        public int NbElements { get; set; }

        public int NbInputs { get; set; }

        public double[] TrainingExemples { get; set; }

        public double[] ExpectedResults { get; set; }

        public int MaxIteration { get; set; }
    }

    LinearTraining createTrainingConfiguration()
    {
        LinearTraining c = new LinearTraining();
        c.NbElements = targetTransforms.Length;
        c.NbInputs = 2;

        c.TrainingExemples = new double[c.NbElements * c.NbInputs];
        c.ExpectedResults = new int[c.NbElements];

        for (int i = 0; i < targetMeshRenderers.Length; ++i)
        {
            MeshRenderer mr = targetMeshRenderers[i].GetComponent<MeshRenderer>();
            if (mr.material.color == redMat.color)
            {
                Transform t = targetTransforms[i].GetComponent<Transform>();
                c.TrainingExemples[i * c.NbInputs] = t.position.x;
                c.TrainingExemples[i * c.NbInputs + 1] = t.position.z;
                c.ExpectedResults[i] = -1;
            }
            if (mr.material.color == blueMat.color)
            {
                Transform t = targetTransforms[i].GetComponent<Transform>();
                c.TrainingExemples[i * c.NbInputs] = t.position.x;
                c.TrainingExemples[i * c.NbInputs + 1] = t.position.z;
                c.ExpectedResults[i] = 1;
            }
        }

        c.MaxIteration = 10000;

        return c;
    }

    LinearTraining2 createTrainingConfiguration2()
    {
        LinearTraining2 c = new LinearTraining2();
        c.NbElements = targetTransforms.Length;
        c.NbInputs = 2;

        c.TrainingExemples = new double[c.NbElements * c.NbInputs];
        c.ExpectedResults = new double[c.NbElements];

        for (int i = 0; i < targetMeshRenderers.Length; ++i)
        {
            MeshRenderer mr = targetMeshRenderers[i].GetComponent<MeshRenderer>();
            if (mr.material.color == redMat.color)
            {
                Transform t = targetTransforms[i].GetComponent<Transform>();
                c.TrainingExemples[i * c.NbInputs] = t.position.x;
                c.TrainingExemples[i * c.NbInputs + 1] = t.position.z;
                c.ExpectedResults[i] = 1;
            }
            if (mr.material.color == blueMat.color)
            {
                Transform t = targetTransforms[i].GetComponent<Transform>();
                c.TrainingExemples[i * c.NbInputs] = t.position.x;
                c.TrainingExemples[i * c.NbInputs + 1] = t.position.z;
                c.ExpectedResults[i] = -1;
            }
        }

        c.MaxIteration = 10000;

        return c;
    }

    void linearScenario(LinearTraining c, System.IntPtr model)
    {
        //printModel(model);

        trainPLA(c.TrainingExemples, c.NbInputs, c.NbElements, c.ExpectedResults, model, c.MaxIteration);

        //printModel(model);

        adjustPlan(model, c.NbInputs);

        removeModel(model);
    }
    void linearScenarioRegression(LinearTraining2 c, System.IntPtr model)
    {
        perceptron_regression(model, c.TrainingExemples, c.NbElements, c.NbInputs, c.ExpectedResults);

        adjustPlan2(model);

        removeModel(model);
    }

    void adjustPlan(System.IntPtr ptrModel, int nbInput)
    {
        for (int i = 0; i < planTargetTransforms.Length; i++)
        {
            Transform t = planTargetTransforms[i].GetComponent<Transform>();

            double[] input = new double[2];
            input[0] = t.position.x;
            input[1] = t.position.z;

            if (classifyLinear(ptrModel, input, 2) == 1)
                t.position += Vector3.up * 1;
        }
    }
    void adjustPlan2(System.IntPtr ptrModel)
    {

        for (int i = 0; i < planTargetTransforms.Length; i++)
        {
            Transform t = planTargetTransforms[i].GetComponent<Transform>();
            MeshRenderer mr = planTargetTransforms[i].GetComponent<MeshRenderer>();

            double[] input = new double[2];
            input[0] = t.position.x;
            input[1] = t.position.z;
            double val = classifyRegression(ptrModel, input, 2);

            //t.position = new Vector3(t.position.x, (float)val, t.position.z);

            val = (val + 1) / 2;


            mr.material.color = new Color((float)val, 0f, (float)(1.0 - val));

        }
    }

    void printModel(System.IntPtr model)
    {
        for (int i = 0; i < planTargetTransforms.Length; i++)
        {
            Transform t = planTargetTransforms[i].GetComponent<Transform>();

            double[] input = new double[2];
            input[0] = t.position.x;
            input[1] = t.position.z;

            Debug.Log(classifyLinear(model, input, 2));
        }

    }


    // Use this for initialization
    void Start()
    {
        Debug.Log("Hello les 5A AL1");
        Debug.Log("From DLL  ==>  : " + Hello42());
        var c = createTrainingConfiguration();

        System.IntPtr model = createModelLinear(c.NbInputs);

        linearScenario(c, model);
        model = createModelLinear(c.NbInputs + 1);
        var c2 = createTrainingConfiguration2();

        linearScenarioRegression(c2, model);
    }

    // Update is called once per frame
    void Update()
    {

    }
}

