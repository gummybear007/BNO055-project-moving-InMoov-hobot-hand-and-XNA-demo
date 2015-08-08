#region File Description
//-----------------------------------------------------------------------------
// SkinningSample.cs
//
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#endregion

#region Using Statements
using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using SkinnedModel;
using Primitives3D;
using System.IO.Ports;
using System.IO;
#endregion


namespace SkinningSample
{
    
    /// <summary>
    /// Sample game showing how to display skinned character animation.
    /// </summary>
    public class SkinningSampleGame : Microsoft.Xna.Framework.Game
    {
        #region Fields

        GraphicsDeviceManager graphics;

        KeyboardState currentKeyboardState = new KeyboardState();
        GamePadState currentGamePadState = new GamePadState();

        KeyboardState previousKeyboardState = new KeyboardState();
        GamePadState previousGamePadState = new GamePadState();

        SkinnedSphere[] skinnedSpheres;
        BoundingSphere[] boundingSpheres;

        bool showSpheres;
        SpherePrimitive spherePrimitive; 
        
        Model currentModel;
        AnimationPlayer animationPlayer;
        SkinningData skinningData;
        Matrix[] boneTransforms;
        Model baseballBat;

        float cameraArc = 0;
        float cameraRotation = 100;
        float cameraDistance = 100;
        float pom;

        #endregion
        char[] x = new char[500];
        int i = 0,stat=0;
        int[] ad = new int[10];
        string rolls;
        char[] rollc = new char[500];

        SpriteFont Font1;
        SpriteBatch napis;
        Quaternion quat,quat2,quat3,q,qu;

        private SerialPort port = new SerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
        #region Initialization


        public SkinningSampleGame()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            graphics.PreferredBackBufferWidth = 1000;
            graphics.PreferredBackBufferHeight = 700;
#if WINDOWS_PHONE
            // Frame rate is 30 fps by default for Windows Phone.
            TargetElapsedTime = TimeSpan.FromTicks(333333);
            
            graphics.IsFullScreen = true;            
#endif
        }


        /// <summary>
        /// Load your graphics content.
        /// </summary>
        protected override void LoadContent()
        {

               

            // Load the model.
            currentModel = Content.Load<Model>("dude");

            // Look up our custom skinning information.
            skinningData = currentModel.Tag as SkinningData;

            if (skinningData == null)
                throw new InvalidOperationException
                    ("This model does not contain a SkinningData tag.");

            boneTransforms = new Matrix[skinningData.BindPose.Count];

            // Load the baseball bat model.
            baseballBat = Content.Load<Model>("baseballbat");

            // Create an animation player, and start decoding an animation clip.
            animationPlayer = new AnimationPlayer(skinningData);

            AnimationClip clip = skinningData.AnimationClips["Take 001"];

            animationPlayer.StartClip(clip);

            // Load the bounding spheres.
            skinnedSpheres = Content.Load<SkinnedSphere[]>("CollisionSpheres");
            boundingSpheres = new BoundingSphere[skinnedSpheres.Length];

            spherePrimitive = new SpherePrimitive(GraphicsDevice, 1, 12);

            // Create a new SpriteBatch, which can be used to draw textures.
            napis = new SpriteBatch(GraphicsDevice);
            Font1 = Content.Load<SpriteFont>("napis1");



            this.port.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            port.Open();   
        }


        #endregion

        #region Update and Draw


        /// <summary>
        /// Allows the game to run logic.
        /// </summary>
        /// 




        protected override void Update(GameTime gameTime)
        {
            
            Quaternion rot;
            rot.W=1f;
            rot.Y=0;
            rot.X = 0;
            rot.Z = 0;

            rot.Normalize();
            
            HandleInput();

            UpdateCamera(gameTime);

            if (currentKeyboardState.IsKeyDown(Keys.NumPad4))
            {
                pom=pom+0.5f;
            }
            if (currentKeyboardState.IsKeyDown(Keys.NumPad6))
            {
                pom = pom - 0.5f;
            }
            // Read gamepad inputs.
            float headRotation = currentGamePadState.ThumbSticks.Left.X;
            float armRotation = Math.Max(currentGamePadState.ThumbSticks.Left.Y, 0);
            float armRotation1 = Math.Max(currentGamePadState.ThumbSticks.Left.Y, 0);

            // Create rotation matrices for the head and arm bones.
            Matrix headTransform = Matrix.CreateRotationX(headRotation);
            Matrix armTransform = Matrix.CreateRotationY(-armRotation);
            Matrix armTransform1 = Matrix.CreateRotationY(armRotation1);
            Matrix thTransform1 = Matrix.CreateRotationY(armRotation1);

            Matrix thumb1rot = Matrix.CreateRotationZ((float)(ad[0]-30) / 90);
            Matrix thumb0rot = Matrix.CreateRotationZ((float)(ad[0] - 30) / 60);
            Matrix thumb2rot = Matrix.CreateRotationZ((float)(ad[1] - 30) / 120) * Matrix.CreateRotationY((float)(ad[1]-15) / 70);

            Matrix index1rot = Matrix.CreateRotationZ((float)(ad[2]-10) / 60);
            Matrix index2rot = Matrix.CreateRotationZ((float)(ad[3]-10) / 60);

            Matrix mid1rot = Matrix.CreateRotationZ((float)(ad[4] - 10) / 60);
            Matrix mid2rot = Matrix.CreateRotationZ((float)(ad[5] - 10) / 60);

            Matrix ring1rot = Matrix.CreateRotationZ((float)(ad[6] - 10) / 60);
            Matrix ring2rot = Matrix.CreateRotationZ((float)(ad[7] - 10) / 60);

            Matrix pink1rot = Matrix.CreateRotationZ((float)(ad[8] - 10) / 60);
            Matrix pink2rot = Matrix.CreateRotationZ((float)(ad[9] -10) / 60);

            // Tell the animation player to compute the latest bone transform matrices.
            //animationPlayer.UpdateBoneTransforms(gameTime.ElapsedGameTime, true);

            // Copy the transforms into our own array, so we can safely modify the values.
            animationPlayer.GetBoneTransforms().CopyTo(boneTransforms, 0);
            
            // Modify the transform matrices for the head and upper-left arm bones.
            int handIndex = skinningData.BoneIndices["L_Hand"];
            int thIndex1 = skinningData.BoneIndices["L_Thumb1"];
            int thIndex2 = skinningData.BoneIndices["L_Thumb2"];
            int thIndex3 = skinningData.BoneIndices["L_Thumb3"];
            int armIndex0 = skinningData.BoneIndices["L_Forearm"];
            int armIndex1 = skinningData.BoneIndices["L_UpperArm"];
            int bod = skinningData.BoneIndices["Root"];

            int Thumb1 = skinningData.BoneIndices["L_Thumb1"];
            int Thumb2 = skinningData.BoneIndices["L_Thumb2"];  
            int Thumb3 = skinningData.BoneIndices["L_Thumb3"];           

            int index1 = skinningData.BoneIndices["L_Index1"];
            int index2 = skinningData.BoneIndices["L_Index2"];
            int index3 = skinningData.BoneIndices["L_Index3"];

            int midle1 = skinningData.BoneIndices["L_Middle1"];
            int midle2 = skinningData.BoneIndices["L_Middle2"];
            int midle3 = skinningData.BoneIndices["L_Middle3"];

            int ring1 = skinningData.BoneIndices["L_Ring1"];
            int ring2 = skinningData.BoneIndices["L_Ring2"];
            int ring3 = skinningData.BoneIndices["L_Ring3"];

            int pinky1 = skinningData.BoneIndices["L_Pinky1"];
            int pinky2 = skinningData.BoneIndices["L_Pinky2"];
            int pinky3 = skinningData.BoneIndices["L_Pinky3"];

            //boneTransforms[headIndex] = Matrix.CreateFromYawPitchRoll(2.0F, 0.0F, 2.0F);
            boneTransforms[Thumb1] = thumb2rot * boneTransforms[Thumb1];
            boneTransforms[Thumb2] = thumb1rot * boneTransforms[Thumb2];
            boneTransforms[Thumb3] = thumb0rot * boneTransforms[Thumb3];

            boneTransforms[index3] = index1rot * boneTransforms[index3];
            boneTransforms[index2] = index1rot * boneTransforms[index2];
            boneTransforms[index1] = index2rot * boneTransforms[index1];

            boneTransforms[midle3] = mid1rot * boneTransforms[midle3];
            boneTransforms[midle2] = mid1rot * boneTransforms[midle2];
            boneTransforms[midle1] = mid2rot * boneTransforms[midle1];

            boneTransforms[ring3] = ring1rot * boneTransforms[ring3];
            boneTransforms[ring2] = ring1rot * boneTransforms[ring2];
            boneTransforms[ring1] = ring2rot * boneTransforms[ring1];

            boneTransforms[pinky3] = pink1rot * boneTransforms[pinky3];
            boneTransforms[pinky2] = pink1rot * boneTransforms[pinky2];
            boneTransforms[pinky1] = pink2rot * boneTransforms[pinky1];

            q = Quaternion.Multiply(Quaternion.Conjugate(Quaternion.CreateFromRotationMatrix(boneTransforms[bod] * Matrix.CreateFromYawPitchRoll(MathHelper.ToRadians(0), MathHelper.ToRadians(-10), MathHelper.ToRadians(pom)))), quat2);
            boneTransforms[armIndex1] = Matrix.CreateFromYawPitchRoll(MathHelper.ToRadians(180), MathHelper.ToRadians(0), MathHelper.ToRadians(0)) * Matrix.CreateFromQuaternion(q) * boneTransforms[armIndex1];

            q = Quaternion.CreateFromRotationMatrix(boneTransforms[armIndex1]);
            q = Quaternion.Multiply(Quaternion.Conjugate(quat2), quat);
            qu.W = q.W;
            qu.X = -q.X;
            qu.Y = q.Y;
            qu.Z = -q.Z;
            boneTransforms[armIndex0] = Matrix.CreateFromQuaternion(qu) * boneTransforms[armIndex0];

            q = Quaternion.Multiply(Quaternion.Conjugate(quat), Quaternion.CreateFromRotationMatrix(Matrix.CreateRotationZ(MathHelper.ToRadians(-90)) *Matrix.CreateFromQuaternion(quat3)));
            qu.W = q.W;
            qu.X = q.X;
            qu.Y = q.Z; 
            qu.Z = -q.Y;
            boneTransforms[handIndex] = Matrix.CreateFromQuaternion(qu)*Matrix.CreateFromYawPitchRoll(MathHelper.ToRadians(180), MathHelper.ToRadians(0), MathHelper.ToRadians(0)) * boneTransforms[handIndex] ;


            // Tell the animation player to recompute the world and skin matrices.
            animationPlayer.UpdateWorldTransforms(Matrix.Identity, boneTransforms);
            animationPlayer.UpdateSkinTransforms();

            UpdateBoundingSpheres(); 
            
            base.Update(gameTime);
        }


        /// <summary>
        /// Updates the boundingSpheres array to match the current animation state.
        /// </summary>
        void UpdateBoundingSpheres()
        {
            // Look up the current world space bone positions.
            Matrix[] worldTransforms = animationPlayer.GetWorldTransforms();

            for (int i = 0; i < skinnedSpheres.Length; i++)
            {
                // Convert the SkinnedSphere description to a BoundingSphere.
                SkinnedSphere source = skinnedSpheres[i];
                Vector3 center = new Vector3(source.Offset, 0, 0);
                BoundingSphere sphere = new BoundingSphere(center, source.Radius);

                // Transform the BoundingSphere by its parent bone matrix,
                // and store the result into the boundingSpheres array.
                int boneIndex = skinningData.BoneIndices[source.BoneName];

                boundingSpheres[i] = sphere.Transform(worldTransforms[boneIndex]);
            }
        }
        
        
        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        protected override void Draw(GameTime gameTime)
        {
         

            GraphicsDevice device = graphics.GraphicsDevice;



            device.Clear(Color.CornflowerBlue);

            Matrix[] bones = animationPlayer.GetSkinTransforms();

            // Compute camera matrices.
            Matrix view = Matrix.CreateTranslation(0,-50, 0) * 
                          Matrix.CreateRotationY(MathHelper.ToRadians(cameraRotation)) *
                          Matrix.CreateRotationX(MathHelper.ToRadians(cameraArc)) *
                          Matrix.CreateLookAt(new Vector3(0, 0, -cameraDistance), 
                                              new Vector3(0, 0, 0), Vector3.Up);

            Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4,
                                                                    device.Viewport.AspectRatio,
                                                                    1,
                                                                    10000);

            // Render the skinned mesh.
            foreach (ModelMesh mesh in currentModel.Meshes)
            {
                foreach (SkinnedEffect effect in mesh.Effects)
                {
                    effect.SetBoneTransforms(bones);

                    effect.View = view;
                    effect.Projection = projection;

                    effect.EnableDefaultLighting();

                    effect.SpecularColor = new Vector3(0.25f);
                    effect.SpecularPower = 16;
                }

        /*        napis.Begin();
                string output = "qw:" + qu.W.ToString("0.00");
                napis.DrawString(Font1, output, new Vector2(10, 0), Color.Red);
                output = "qx:" + qu.X.ToString("0.00");
                napis.DrawString(Font1, output, new Vector2(10, 30), Color.Red);
                output = "qy:" + qu.Y.ToString("0.00");
                napis.DrawString(Font1, output, new Vector2(10, 60), Color.Red);
                output = "qz:" + qu.Z.ToString("0.00");
                napis.DrawString(Font1, output, new Vector2(10, 90), Color.Red);
                napis.End();*/

                mesh.Draw();
            }

          //  DrawBaseballBat(view, projection);

            if (showSpheres)
            {
                DrawBoundingSpheres(view, projection);
            }


            base.Draw(gameTime);
        }


        /// <summary>
        /// Draws the animated bounding spheres.
        /// </summary>
        void DrawBoundingSpheres(Matrix view, Matrix projection)
        {
            GraphicsDevice.RasterizerState = Wireframe;

            foreach (BoundingSphere sphere in boundingSpheres)
            {
                Matrix world = Matrix.CreateScale(sphere.Radius) *
                               Matrix.CreateTranslation(sphere.Center);

                spherePrimitive.Draw(world, view, projection, Color.White);
            }

            GraphicsDevice.RasterizerState = RasterizerState.CullCounterClockwise;
        }


        static RasterizerState Wireframe = new RasterizerState
        {
            FillMode = FillMode.WireFrame
        };


        /// <summary>
        /// Draws the baseball bat.
        /// </summary>
        void DrawBaseballBat(Matrix view, Matrix projection)
        {
            int handIndex = skinningData.BoneIndices["L_Index1"];

            Matrix[] worldTransforms = animationPlayer.GetWorldTransforms();

            // Nudge the bat over so it appears between the left thumb and index finger.
            Matrix batWorldTransform = Matrix.CreateFromQuaternion(quat) *
                                       worldTransforms[handIndex];

            foreach (ModelMesh mesh in baseballBat.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.World = batWorldTransform;
                    effect.View = view;
                    effect.Projection = projection;

                    effect.EnableDefaultLighting();
                }

                mesh.Draw();
            }
        }
        #endregion

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {

            while (port.BytesToRead > 0)
            {

                port.Read(x, i, 1);
                if (x[i] == '\r')
                {
                    zobraz();
                    i = 0;
                }
                i++;
                if (i > 499)
                {
                    i = 0;
                }
            }
        }


        private void zobraz()
        {
          
            string s = new string(x);
            string q;
            int quat_num,ad_num,j;

            long del = 16384;
            
            for (quat_num = 1; quat_num < 13; quat_num++)
            {
                q = "quat" + quat_num + ":";
                if (s.Contains(q))
                {
                    int i = s.IndexOf(q) + q.Length;
                    j = i;

                    while (x[i] != '\t' && x[i] != '\r' && (i - j) < 100)
                    {
                        rollc[i - j] = x[i];
                        i++;
                    }
                    q = rollc[0].ToString();

                    rolls = string.Join("", rollc);

                    try
                    {
                        switch (quat_num)
                        {
                            case 1:
                                quat.W= (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 2:
                                quat.X = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 3:
                                quat.Y = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 4:
                                quat.Z = (float)Convert.ToDouble(rolls) / del;
                                break;

                            case 5:
                                quat2.W = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 6:
                                quat2.X = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 7:
                                quat2.Y = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 8:
                                quat2.Z = (float)Convert.ToDouble(rolls) / del;
                                break;

                            case 9:
                                quat3.W = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 10:
                                quat3.X = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 11:
                                quat3.Y = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 12:
                                quat3.Z = (float)Convert.ToDouble(rolls) / del;
                                break;
                            default:
                                break;
                        }
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("Unable to convert '{0}' to a Double.", rolls);
                    }
                    Array.Clear(rollc, 0, rollc.Length);
                }

            }


            for (ad_num = 1; ad_num < 11; ad_num++) //vyber postupnì všechny data ad pøevodníkù z øetìzce
            {
                q = "ad" + ad_num + ":";            //formát dat v øetìzci

                if (s.Contains(q))
                {
                    int i = s.IndexOf(q) + q.Length; //do pamìti následující znak obsahující první èíslici
                    j = i;


                    while (x[i] != '\t' && x[i] != '\r' && (i - j) < 100) //vyber znaky ke speciálnímu znaku
                    {
                        rollc[i - j] = x[i];                      //ulož do char[] pole
                        i++;
                    }


                    rolls = string.Join("", rollc);                 //pøeveï char[] pole na string

                    try
                    {
                        ad[ad_num - 1] = (int)Convert.ToDouble(rolls);  //konverze stringu obsahujícího èíslice na èíslo int
                    }
                    catch (FormatException)                         //vyjímka pøevodu
                    {
                        System.Console.WriteLine("Unable to convert '{0}' to a Int.", rolls);
                    }
                    Array.Clear(rollc, 0, rollc.Length);
                }
            }

        }


        

        #region Handle Input


        /// <summary>
        /// Handles input for quitting the game.
        /// </summary>
        private void HandleInput()
        {
            previousKeyboardState = currentKeyboardState;
            previousGamePadState = currentGamePadState;

            currentKeyboardState = Keyboard.GetState();
            currentGamePadState = GamePad.GetState(PlayerIndex.One);

            // Check for exit.
            if (currentKeyboardState.IsKeyDown(Keys.Escape) ||
                currentGamePadState.Buttons.Back == ButtonState.Pressed)
            {
                Exit();
            }

            // Toggle the collision sphere display.
            if ((currentKeyboardState.IsKeyDown(Keys.Enter) &&
                 previousKeyboardState.IsKeyUp(Keys.Enter)) ||
                (currentGamePadState.IsButtonDown(Buttons.A) &&
                 previousGamePadState.IsButtonUp(Buttons.A)))
            {
                showSpheres = !showSpheres;
            }
        }


        /// <summary>
        /// Handles camera input.
        /// </summary>
        private void UpdateCamera(GameTime gameTime)
        {
            float time = (float)gameTime.ElapsedGameTime.TotalMilliseconds;

            // Check for input to rotate the camera up and down around the model.
            if (currentKeyboardState.IsKeyDown(Keys.Up) ||
                currentKeyboardState.IsKeyDown(Keys.W))
            {
                cameraArc += time * 0.1f;
            }
            
            if (currentKeyboardState.IsKeyDown(Keys.Down) ||
                currentKeyboardState.IsKeyDown(Keys.S))
            {
                cameraArc -= time * 0.1f;
            }

            cameraArc += currentGamePadState.ThumbSticks.Right.Y * time * 0.25f;

            // Limit the arc movement.
            if (cameraArc > 90.0f)
                cameraArc = 90.0f;
            else if (cameraArc < -90.0f)
                cameraArc = -90.0f;

            // Check for input to rotate the camera around the model.
            if (currentKeyboardState.IsKeyDown(Keys.Right) ||
                currentKeyboardState.IsKeyDown(Keys.D))
            {
                cameraRotation += time * 0.1f;
            }

            if (currentKeyboardState.IsKeyDown(Keys.Left) ||
                currentKeyboardState.IsKeyDown(Keys.A))
            {
                cameraRotation -= time * 0.1f;
            }

            cameraRotation += currentGamePadState.ThumbSticks.Right.X * time * 0.25f;

            // Check for input to zoom camera in and out.
            if (currentKeyboardState.IsKeyDown(Keys.Z))
                cameraDistance += time * 0.25f;

            if (currentKeyboardState.IsKeyDown(Keys.X))
                cameraDistance -= time * 0.25f;

            cameraDistance += currentGamePadState.Triggers.Left * time * 0.5f;
            cameraDistance -= currentGamePadState.Triggers.Right * time * 0.5f;

            // Limit the camera distance.
            if (cameraDistance > 500.0f)
                cameraDistance = 500.0f;
            else if (cameraDistance < 10.0f)
                cameraDistance = 10.0f;

            if (currentGamePadState.Buttons.RightStick == ButtonState.Pressed ||
                currentKeyboardState.IsKeyDown(Keys.R))
            {
                cameraArc = 0;
                cameraRotation = 0;
                cameraDistance = 100;
            }
        }


        #endregion
    }


    #region Entry Point

    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    static class Program
    {
        static void Main()
        {
            using (SkinningSampleGame game = new SkinningSampleGame())
            {
                game.Run();
            }
        }
    }

    #endregion
}
