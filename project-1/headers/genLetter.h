class letter
{
public:
    int size;
    letter(int size)
    {
        this->size = size - 1;
    }
    void setCoordinates(GLfloat v[][3], bool pos[])
    {
        cube *a = NULL;
        for(int i = 0; i < size; i++)
        {
            if((pos[i] == false && v[i][1] < v[i+1][1]) || (pos[i] == true && v[i][0] > v[i+1][0]))
            {
                a = new cube(v[i + 1], v[i], pos[i]);
            }
            else
            {
                a = new cube(v[i], v[i + 1], pos[i]);
                cout<<"entra"<<endl;
            }
        }
    }
};
