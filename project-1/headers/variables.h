static int winwidth,winheight;
static int mx,my;
static int flag=0;
static float rotx=0.0f, roty=0.0f;

GLuint rendering_program;
GLuint vertex_array_object;
GLuint shader;
unsigned int VBO, VAO, EBO, VBN;

vector<GLfloat> g_vertex_buffer_data;
vector<GLfloat> normals;
vector<GLuint> indices;

GLfloat Gv[6][3]={{-2,1,0.0}, {-4,1,0.0}, {-4,-1,0.0}, {-2,-1,0.0}, {-2,0,0.0}, {-3,0,0.0}};
GLfloat Wv[5][3]={{-2,1,0.0}, {-1.25,-1,0.0}, {-1,0,0.0}, {-0.75,-1,0.0}, {0,1,0.0}};
GLfloat Vv[3][3]={{0,1,0.0}, {1,-1,0.0}, {2,1,0.0}};
GLfloat Av[5][3]={{2,-1,0.0}, {3,1,0.0}, {4,-1,0.0}, {3.5,0,0.0}, {2.5,0,0.0}};
GLfloat Xv[][3]={{-3.0,0.0,0.0}, {3.0,0.0,0.0}};

bool g[5] = {true, false, true, false, true};
bool w[4] = {false, false, false, false};
bool v[2] = {false, false};
bool a[4] = {false, false, false, true};
//bool x[] = {true};
//X.setCoordinates(Xv, x);
